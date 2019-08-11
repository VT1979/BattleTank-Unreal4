// Fill out your copyright notice in the Description page of Project Settings.



#include "TankPlayerController.h"
//#include "BattleTank.h" (instructor has it in vide, is it necessary?)

// Tick
	// Super
	// Aim towards crosshair

void::ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//FString PossesedTank;

	ATank* PossessedTank = GetControlledTank();

	if (PossessedTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play, with %s"), *PossessedTank->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController does not possess a Tank!"))
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

	FVector HitLocation; //Out paramter

	if (GetSightRayHitLocation(HitLocation))
	{
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());

		// Get world location, if linetrace through crosshair, if it hits landscape tell controlled tank to aim at this point
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
		UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *LookDirection.ToString())
	}

	//OutHitLocation = FVector(1.0f);
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