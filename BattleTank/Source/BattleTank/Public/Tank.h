// Copyright Evangelos Tsesmelidakis (for educaltional purposes only)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // must always be last

// Forward declarations
class UTankAimingComponent;
class UTankMovementComponent;
class UTankBarrel;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public: 
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();

protected:
	UPROPERTY(BlueprintREadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;
	
	UPROPERTY(BlueprintREadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;

	// Local barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr; //TODO Remove after refactoring

	virtual void BeginPlay() override;

private:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000.0f; //TODO find a sensible default

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3.0f;

	double LastFireTime;

	

};
