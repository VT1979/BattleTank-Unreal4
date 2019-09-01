// Copyright Vaggelis Tsesmelidakis (educational use)


#include "SprungWheel.h"
#include "Components\StaticMeshComponent.h"
#include "PhysicsEngine\PhysicsConstraintComponent.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Chassis = CreateDefaultSubobject<UStaticMeshComponent>(FName("Chassis"));
	SetRootComponent(Chassis);
	

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Chassis);

	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Physics Constraint"));
	PhysicsConstraint->SetupAttachment(Chassis);
	
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

