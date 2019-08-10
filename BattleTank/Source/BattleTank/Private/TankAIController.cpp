// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ATank* PossessedTank = GetControlledTank();
	ATank* PlayerTank = GetPlayerTank();

	if (PossessedTank && PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController is possessing %s and found player-controlled tank %s"), *PossessedTank->GetName(), *PlayerTank->GetName())
	}
	else
	{
		if (!PossessedTank)
			UE_LOG(LogTemp, Error, TEXT("TankAIController did not possess a tank"))
		if(!PlayerTank)
			UE_LOG(LogTemp, Error, TEXT("TankAIController did not find player-controlled tank"))
	}

}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
		
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
