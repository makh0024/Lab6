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
};
