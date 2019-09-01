// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Components\SceneComponent.h"


void ATank::BeginPlay()
{
	Super::BeginPlay();	// NEEDED for Blueprint BeginPlay() to run. VERY IMPORTANT!

	CurrentHealth = StartingHealth;
}

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	auto DamageToApply = FPlatformMath::RoundToInt(Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser));
	DamageToApply = FMath::Clamp<int32>(DamageToApply, 0, CurrentHealth);
	CurrentHealth -= DamageToApply;

	if (CurrentHealth == 0)
	{
		TankDies.Broadcast();
	}

	return DamageToApply;
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}