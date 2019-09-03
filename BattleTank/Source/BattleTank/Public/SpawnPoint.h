// Copyright Vaggelis Tsesmelidakis (educational use)

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpawnPoint.generated.h"

class ASprungWheel;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API USpawnPoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnPoint();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	AActor* GetTankSuspension() const { return TankSuspension; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	


private:
	//	Config

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<ASprungWheel> SuspensionSystemBlueprint;

	UPROPERTY()
	AActor* TankSuspension;
};
