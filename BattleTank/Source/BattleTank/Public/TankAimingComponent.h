// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UENUM() //Unreal Engine's coding standard to introduce Enumerations

enum class EFiringState : uint8 
{ 
	Reloading,
	Aiming,
	Locked, 
	OutOfAmmo
};


//Forward Declarations
class UTankBarrel;
class UTankTurret;
class AProjectile;

//Hold's Barrel's Elevate and aiming properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();
	
	// Called when the game starts
	virtual void BeginPlay() override;
	
	void AimAt(FVector HitLocation);

	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int GetAmmunitionRounds() const;
		
protected:
	UPROPERTY(BlueprintReadonly, Category = "State")
	EFiringState FiringState = EFiringState::Aiming;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void MoveBarrel(FVector AimDirection);

	bool IsBarrelMoving();

	FVector AimDirection;

	double LastFireTime;

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3.0f;


	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 8000.0f; 

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int AmmunitionRounds = 3;
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;
		
};
