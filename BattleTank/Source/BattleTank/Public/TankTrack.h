// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force and to apply forces to the tank 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

	
public:
	// Sets a throttle value between -1 and +1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float TrackMaxDrivingForce = 40000000; // Assume 40-ton tank at 10m/s/s (1g) acceleration

private:
	UTankTrack();

	virtual void BeginPlay() override;

	TArray<class ASprungWheel*> GetWheels() const;	// This includes a forward declaration for ASprungWheel as well. I could have also done "class ASprungWheel;" up top and just included "TArray<SprungWheel*> here

	void DriveTrack(float CurrentThrottle);
};


