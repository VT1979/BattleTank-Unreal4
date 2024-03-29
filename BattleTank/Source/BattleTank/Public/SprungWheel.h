// Copyright Vaggelis Tsesmelidakis (educational use)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

//class UStaticMeshComponent;
class USphereComponent;
class UPhysicsConstraintComponent;

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void AddDrivingForce(float ForceMagnitude);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

private:
	//Components
	UPROPERTY(EditAnywhere, Category = "Components")
	USphereComponent* Wheel = nullptr;

	UPROPERTY(EditAnywhere, Category = "Components")
	USphereComponent* Axle = nullptr;
	
	UPROPERTY(EditAnywhere, Category = "Components")
	UPhysicsConstraintComponent* PhysicsConstraint = nullptr;

	UPROPERTY(EditAnywhere, Category = "Components")
	UPhysicsConstraintComponent* AxleWheelConstraint = nullptr;

	float TotalForceMagnitudeThisFrame = 0.f;

	void SetupConstraints();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void ApplyForce();
};
