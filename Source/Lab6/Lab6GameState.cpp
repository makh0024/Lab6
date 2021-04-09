// Fill out your copyright notice in the Description page of Project Settings.


#include "Lab6GameState.h"
#include "Lab6GameMode.h"
#include "Net/UnrealNetwork.h"

ALab6GameState::ALab6GameState()
{
	SetReplicates(true);
}

void ALab6GameState::Respawn()
{
	ALab6GameMode* GM = Cast<ALab6GameMode>(GetWorld()->GetAuthGameMode());

	if (GM)
	{
		GM->NextLevel();
	}
}