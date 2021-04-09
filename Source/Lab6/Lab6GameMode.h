// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Lab6GameMode.generated.h"

UCLASS(minimalapi)
class ALab6GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALab6GameMode();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gameplay)
        int TeamOneScore = 0;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gameplay)
        int TeamTwoScore = 0;

    void RespawnPlayer(APlayerController* NewPlayer, int playerTeam);

    class APickupSpawner* GetSpawner();

    void NextLevel();

    void SetPlayerMaterials(class ALab6Character* pCharacter);

    int GetTeam1PickupsLeft();
    int GetTeam2PickupsLeft();
};



