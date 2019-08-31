// Copyright Evangelos Tsesmelidakis (for educaltional purposes only)

#pragma once

#include "CoreMinimal.h"
#include "Tank.generated.h" // must always be last

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public: 
	// Called by the Engine when damage is dealt
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;


protected:

	// Local barrel reference for spawning projectile

	virtual void BeginPlay() override;

private:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100.f;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth = StartingHealth;
};
