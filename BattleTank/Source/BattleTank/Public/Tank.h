// Copyright Evangelos Tsesmelidakis (for educaltional purposes only)

#pragma once

#include "CoreMinimal.h"
#include "Tank.generated.h" // must always be last

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public: 

	

protected:

	// Local barrel reference for spawning projectile

	virtual void BeginPlay() override;

private:
	// Sets default values for this pawn's properties
	ATank();
};
