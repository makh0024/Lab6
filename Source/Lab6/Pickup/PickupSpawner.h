// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupSpawner.generated.h"

UCLASS()
class LAB6_API APickupSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(Server, Reliable)
		void SpawnPickups();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf <class APickupActor> PickupToSpawn;

protected:

	int MaxPickups = 5;
	float MaxPosRange = 1000.f;
	float MinPosRange = -1000.f;

	FTimerHandle SpawnTimerHandler;
};
