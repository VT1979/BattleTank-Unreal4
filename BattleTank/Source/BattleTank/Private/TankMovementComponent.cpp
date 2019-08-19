// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
	
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

	//TODO fix the double speed issue if we combine inputs (stick axis plus triggers)
}

void UTankMovementComponent::IntendTurnRight(float Throw) {

	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-3*Throw);

	//TODO fix the double speed issue if we combine inputs (stick axis plus triggers)
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call Super() as we're replacing the functionality
	
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	IntendMoveForward(FVector::DotProduct(TankForward, AIForwardIntention));	//DotProduct returns a float...
	IntendTurnRight(FVector::CrossProduct(TankForward, AIForwardIntention).Z);	//... whereas CrossProduct returns a FVector, whose Z component we need (that IS a float)
	
	//UE_LOG(LogTemp, Warning, TEXT("%s RequestDirectMove(): %f"), *GetOwner()->GetName(), *MoveVelocity.GetSafeNormal().ToString())
}
