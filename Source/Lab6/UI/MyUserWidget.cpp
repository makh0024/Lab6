// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"

#include "Components/TextBlock.h"
#include "../Lab6GameMode.h"
#include "../Lab6GameState.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

bool UMyUserWidget::Initialize()
{
    bool bResult = Super::Initialize();
    if (!bResult)
    {
        return false;
    }

    return true;
}

void UMyUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    DisplayPickupsLeft();
}

void UMyUserWidget::DisplayPickupsLeft_Implementation()
{
    UTextBlock* Widget = Cast<UTextBlock>(GetWidgetFromName("TextBlock1"));
    if (Widget != nullptr)
    {
        ALab6GameState* GS = Cast<ALab6GameState>(GetWorld()->GetGameState());

        if (GS)
        {
            GS->SetTeam1PickupsLeft();
            //Team1 = GS->GetTeam1PickupsLeft();
            Team1 = GS->Team1Pickups;

            Widget->SetText(FText::FromString(FString::Printf(TEXT("Team 1 Pickups Left: %i"), Team1)));
        }
    }

    UTextBlock* Widget2 = Cast<UTextBlock>(GetWidgetFromName("TextBlock2"));
    if (Widget2 != nullptr)
    {
        ALab6GameState* GS = Cast<ALab6GameState>(GetWorld()->GetGameState());

        if (GS)
        {
            GS->SetTeam2PickupsLeft();
            //Team2 = GS->GetTeam2PickupsLeft();
            Team2 = GS->Team2Pickups;

            Widget2->SetText(FText::FromString(FString::Printf(TEXT("Team 2 Pickups Left: %i"), Team2)));
        }

    }
}