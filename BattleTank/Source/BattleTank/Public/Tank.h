// Copyright Evangelos Tsesmelidakis (for educaltional purposes only)

#pragma once

#include "CoreMinimal.h"
#include "Tank.generated.h" // must always be last

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathEvent);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public: 
	// Delegate for notifying of Tank's death in the game
	FDeathEvent TankDies;

	// Called by the Engine when damage is dealt
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// Returns Current Health as a percentage of Starting Health between 0% and 100%
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

protected:

	// Local barrel reference for spawning projectile

	virtual void BeginPlay() override;

private:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100.f;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth; // Initilized in BeginPlay()

};
