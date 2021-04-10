// Fill out your copyright notice in the Description page of Project Settings.


#include "Lab6PlayerController.h"
#include "UI/MyUserWidget.h"

void ALab6PlayerController::BeginPlay()
{
	Super::BeginPlay();
		
	if (GameInfoBP != nullptr  && IsLocalController())
	{
		GameInfoWidget = CreateWidget<UMyUserWidget>(this, GameInfoBP);
		GameInfoWidget->AddToViewport();
	}
	
}

//void ALab6PlayerController::Tick(float DeltaTime)
//{

//void ALab6PlayerController::FeedNumPickups(int team1, int team2)
//{
//	GameInfoWidget->DisplayPickupsLeft(team1, team2);
//}