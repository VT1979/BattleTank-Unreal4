// Fill out your copyright notice in the Description page of Project Settings.



#include "TankPlayerController.h"
//#include "BattleTank.h" (instructor has it in vide, is it necessary?)

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

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
