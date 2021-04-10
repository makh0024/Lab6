// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Lab6PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LAB6_API ALab6PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;

	//virtual void Tick(float DeltaTime) override;

	UPROPERTY()
		class UMyUserWidget* GameInfoWidget;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UMyUserWidget> GameInfoBP;

	//void FeedNumPickups(int team1, int team2);
};
