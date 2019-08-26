// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"


/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = "Setup") // Might consider doing EditDefaultsOnly
	float AcceptanceRadius = 8000; // Remember this represents cm

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	//How close the AI tank can get close to a player
	
};
