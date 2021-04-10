// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Lab6GameState.generated.h"

/**
 * 
 */
UCLASS()
class LAB6_API ALab6GameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ALab6GameState();

	void Respawn();

	int GetTeam1PickupsLeft();
	int GetTeam2PickupsLeft();

	void SetTeam1PickupsLeft();
	void SetTeam2PickupsLeft();

	UPROPERTY(Replicated)
		int Team1Pickups;

	UPROPERTY(Replicated)
		int Team2Pickups;
};
