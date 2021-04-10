// Fill out your copyright notice in the Description page of Project Settings.


#include "Lab6GameState.h"
#include "Lab6GameMode.h"
#include "Net/UnrealNetwork.h"

#include "Lab6Character.h"
#include "Kismet/GameplayStatics.h"
#include "Pickup/PickupSpawner.h"
#include "Pickup/PickupActor.h"
#include "Lab6PlayerController.h"

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

int ALab6GameState::GetTeam1PickupsLeft()
{
    TArray<AActor*> Players;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALab6Character::StaticClass(), Players);

    for (int i = 0; i < Players.Num(); i++)
    {
        ALab6Character* player = Cast<ALab6Character>(Players[i]);

        if (player->PlayerTeam == 1)
            return player->numPickupsLeft;
    }

    return 1;
}

int ALab6GameState::GetTeam2PickupsLeft()
{
    TArray<AActor*> Players;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALab6Character::StaticClass(), Players);

    for (int i = 0; i < Players.Num(); i++)
    {
        ALab6Character* player = Cast<ALab6Character>(Players[i]);

        if (player->PlayerTeam == 2)
            return player->numPickupsLeft;
    }

    return 2;
}

void ALab6GameState::SetTeam1PickupsLeft()
{
    TArray<AActor*> Players;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALab6Character::StaticClass(), Players);

    for (int i = 0; i < Players.Num(); i++)
    {
        ALab6Character* player = Cast<ALab6Character>(Players[i]);

        if (player->PlayerTeam == 1)
        {
            Team1Pickups = player->numPickupsLeft;
        }
    }
}

void ALab6GameState::SetTeam2PickupsLeft()
{
    TArray<AActor*> Players;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALab6Character::StaticClass(), Players);

    for (int i = 0; i < Players.Num(); i++)
    {
        ALab6Character* player = Cast<ALab6Character>(Players[i]);

        if (player->PlayerTeam == 2)
            Team2Pickups = player->numPickupsLeft;
    }
}

void ALab6GameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ALab6GameState, Team1Pickups);
    DOREPLIFETIME(ALab6GameState, Team2Pickups);
}