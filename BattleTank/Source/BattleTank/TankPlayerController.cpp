// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Public/Tank.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

//#include "BattleTank.h" (instructor has it in vide, is it necessary?)

// Tick
	// Super
	// Aim towards crosshair

void::ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent)
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController can't find AimingComponent at BeginPlay"))
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector OutHitLocation; //Out parameter

	if (GetSightRayHitLocation(OutHitLocation))
	{
		GetControlledTank()->AimAt(OutHitLocation);
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *OutHitLocation.ToString())
	}
	
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // Not needed - to be ignored
	
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult OutHitResult;

	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
		OutHitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility
	))
	{
		OutHitLocation = OutHitResult.Location;
		return true;
	}

	OutHitLocation = FVector(0.f);
	return true;
}