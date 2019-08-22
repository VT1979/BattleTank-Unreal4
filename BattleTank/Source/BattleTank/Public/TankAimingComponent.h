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
	Locked 
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

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void AimAt(FVector HitLocation);
		
protected:
	UPROPERTY(BlueprintReadonly, Category = "State")
	EFiringState FiringState = EFiringState::Aiming;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	void MoveBarrel(FVector AimDirection);

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3.0f;

	double LastFireTime;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000.0f; //TODO find a sensible default

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;
		
};
