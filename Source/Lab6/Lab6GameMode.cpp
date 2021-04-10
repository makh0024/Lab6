// Copyright Epic Games, Inc. All Rights Reserved.

#include "Lab6GameMode.h"
#include "Lab6Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Lab6Character.h"
#include "Kismet/GameplayStatics.h"
#include "Pickup/PickupSpawner.h"
#include "Pickup/PickupActor.h"
#include "Lab6PlayerController.h"
ALab6GameMode::ALab6GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

    static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/BP_Lab6PlayerController"));
    if (PlayerControllerBPClass.Class != NULL)
    {
        PlayerControllerClass = PlayerControllerBPClass.Class;
    }
    //SetReplicates(true);
}

void ALab6GameMode::RespawnPlayer(APlayerController* NewPlayer, int playerTeam)
{
    TArray<AActor*> PlayerStarts;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALab6Character::StaticClass(), PlayerStarts);

    APawn* pawn = SpawnDefaultPawnFor(NewPlayer, PlayerStarts[0]);
    if (pawn)
    {
        if (Cast<ALab6Character>(pawn))
        {
            Cast<ALab6Character>(pawn)->PlayerTeam = playerTeam;
            Cast<ALab6Character>(pawn)->numPickupsLeft = 0;

            TArray<AActor*> Pickups;
            UGameplayStatics::GetAllActorsOfClass(GetWorld(), APickupActor::StaticClass(), Pickups);

            for (int i = 0; i < Pickups.Num(); i++)
            {
                APickupActor* pickup = Cast<APickupActor>(Pickups[i]);

                if (pickup->Team == Cast<ALab6Character>(pawn)->PlayerTeam)
                {
                    Cast<ALab6Character>(pawn)->numPickupsLeft++;
                }
            }

            SetPlayerMaterials(Cast<ALab6Character>(pawn));

            NewPlayer->SetPawn(pawn);
            RestartPlayer(NewPlayer);

        }
        //ENDIF
    }
    //ENDIF
}

APickupSpawner* ALab6GameMode::GetSpawner()
{
    TArray<AActor*> Spawners;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APickupSpawner::StaticClass(), Spawners);

    APickupSpawner* spawner = Cast<APickupSpawner>(Spawners[0]);

    return spawner;
}

void ALab6GameMode::NextLevel()
{
    TArray<AActor*> Spawners;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APickupSpawner::StaticClass(), Spawners);

    for (int i = 0; i < Spawners.Num(); i++)
    {
        APickupSpawner* spawner = Cast<APickupSpawner>(Spawners[i]);

        spawner->SpawnPickups();
    }

    TArray<AActor*> Players;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALab6Character::StaticClass(), Players);

    for (int i = 0; i < Players.Num(); i++)
    {
        ALab6Character* player = Cast<ALab6Character>(Players[i]);

        RespawnPlayer(Cast<APlayerController>(player->GetController()), player->PlayerTeam);
        player->Destroy();
    }
}

void ALab6GameMode::SetPlayerMaterials(class ALab6Character* pCharacter)
{
    if (pCharacter->PlayerTeam == 1)
    {

        UMaterialInstance* material = UMaterialInstanceDynamic::Create(pCharacter->Team1Material, pCharacter);
        pCharacter->GetMesh()->SetMaterial(0, material);
    }
    else
    {
        UMaterialInstance* material = UMaterialInstanceDynamic::Create(pCharacter->Team2Material, pCharacter);
        pCharacter->GetMesh()->SetMaterial(0, material);
    }
}

int ALab6GameMode::GetTeam1PickupsLeft()
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

int ALab6GameMode::GetTeam2PickupsLeft()
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