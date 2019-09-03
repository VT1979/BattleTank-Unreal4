// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = true;

	SetNotifyRigidBodyCollision(true);
}

void UTankTrack::BeginPlay() {
	
	Super::BeginPlay();
}

TArray<class ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> FoundWheels;
	TArray<USceneComponent*> ChildrenComponents;
	GetChildrenComponents(true, OUT ChildrenComponents);

	for (USceneComponent* Child : ChildrenComponents)
	{
		auto SpawnPointChild = Cast<USpawnPoint>(Child);
		if (!SpawnPointChild) continue;

		AActor* SpawnedChild = SpawnPointChild->GetTankSuspension();
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SprungWheel) continue;

		FoundWheels.Add(SprungWheel);
	}


	return FoundWheels;
}




void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -2, 2);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	
	auto Wheels = GetWheels();
	auto ForcePerWheel = ForceApplied / Wheels.Num();

	for (ASprungWheel* Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForceApplied);
	}
}

