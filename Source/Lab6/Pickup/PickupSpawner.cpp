// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupSpawner.h"

#include "PickupActor.h"
#include "Net/UnrealNetwork.h"

// Sets default values
APickupSpawner::APickupSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetReplicates(true);
}

// Called when the game starts or when spawned
void APickupSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	 SpawnPickups();
}

// Called every frame
void APickupSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupSpawner::SpawnPickups_Implementation()
{
	FActorSpawnParameters SpawnParam;
	SpawnParam.Owner = this;
	//SpawnParam.Instigator = this; NOT A PAWN

	for (int i = 0; i < MaxPickups; i++)
	{
		float X = FMath::RandRange(MinPosRange, MaxPosRange);
		float Y = FMath::RandRange(MinPosRange, MaxPosRange);

		FVector StartPosition = GetActorLocation();
		StartPosition += FVector(X, Y, 100.0f);
		FRotator StartRotation = GetActorForwardVector().Rotation();

		GetWorld()->SpawnActor(PickupToSpawn, &StartPosition, &StartRotation, SpawnParam);
	}
}