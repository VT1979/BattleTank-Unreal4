// Copyright Vaggelis Tsesmelidakis (educational use)


#include "SpawnPoint.h"
#include "GameFramework\Actor.h"
#include "Kismet\GameplayStatics.h"
#include "SprungWheel.h"

// Sets default values for this component's properties
USpawnPoint::USpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	auto TankSuspension = GetWorld()->SpawnActorDeferred<ASprungWheel>(SuspensionSystemBlueprint, GetComponentTransform());
	if (!TankSuspension) { return; }
	TankSuspension->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);	// We use KeepWorldTransform here because we already specify the spawn location up above to be the component's location
	UGameplayStatics::FinishSpawningActor(TankSuspension, GetComponentTransform());
	



	// ...
	
}


// Called every frame
void USpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

