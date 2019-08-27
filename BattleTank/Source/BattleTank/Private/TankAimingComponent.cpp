// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds(); // so that everyone has to wait before firing when the game first starts



	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (RemainingAmmoRounds == 0)
	{
		FiringState = EFiringState::OutOfAmmo;
	}
	else
	{
		if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
		{
			FiringState = EFiringState::Reloading;
		}
		else if (IsBarrelMoving())
		{
			FiringState = EFiringState::Aiming;
		}
		else
		{
			FiringState = EFiringState::Locked;
		}
	}
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }
	if (!ensure(Turret)) { return; }

	auto OurTankName = GetOwner()->GetName();
	auto BarrelLocation = Barrel->GetComponentLocation();
	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
		(
			this,
			OutLaunchVelocity,
			StartLocation,
			HitLocation,
			LaunchSpeed,
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace
		);
	
	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();

		MoveBarrel(AimDirection);
	}

	// else do nothing

	// have to find a way to make AimDirection visible to bIsBarrelMoving()
	// so moved it as a private class member
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

int UTankAimingComponent::GetRemainingAmmoRounds() const
{
	return RemainingAmmoRounds;
}

int UTankAimingComponent::GetMaxAmmoRounds() const
{
	return MaxAmmoRounds;
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	if (!ensure(Barrel)) { return; }
	if (!ensure(Turret)) { return; }

	// Work out difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	
	// The following if/else test determines how the turret should move (clock-/anti-clock wise) avoiding turning the long way around to the aiming spot
	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	
	else
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	return !Barrel->GetForwardVector().Equals(AimDirection, 0.1);
}

void UTankAimingComponent::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("After Fire() called RemainingRounds set to: %i"), RemainingAmmoRounds)
	if (!ensure(Barrel)) { return; }
	if (!ensure(ProjectileBlueprint)) { return; }


	if (FiringState == EFiringState::Aiming || FiringState == EFiringState::Locked)
	{	
		// Spawn a projectile at the socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();

		if (RemainingAmmoRounds > 0) // No point letting the value go subzero...
		{
			RemainingAmmoRounds -= 1;
		}

	}

}
