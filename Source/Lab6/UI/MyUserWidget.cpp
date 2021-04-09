// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"

#include "Components/TextBlock.h"
#include "../Lab6GameMode.h"
#include "Kismet/GameplayStatics.h"

bool UMyUserWidget::Initialize()
{
    bool bResult = Super::Initialize();
    if (!bResult)
    {
        return false;
    }

    UTextBlock* Widget = Cast<UTextBlock>(GetWidgetFromName("TextBlock1"));
    if (Widget != nullptr)
    {
        Widget->SetText(FText::FromString("SomeText"));
    }

    ALab6GameMode* GM = Cast<ALab6GameMode>(GetWorld()->GetAuthGameMode());

    if (GM)
    {
        Team1 = GM->GetTeam1PickupsLeft();
        Team2 = GM->GetTeam2PickupsLeft();
    }

    return true;
}

void UMyUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    DisplayPickupsLeft();
}

void UMyUserWidget::DisplayPickupsLeft()
{
    UTextBlock* Widget = Cast<UTextBlock>(GetWidgetFromName("TextBlock1"));
    if (Widget != nullptr)
    {
        ALab6GameMode* GM = Cast<ALab6GameMode>(GetWorld()->GetAuthGameMode());

        if (GM)
        {
            Team1 = GM->GetTeam1PickupsLeft();

            Widget->SetText(FText::FromString(FString::Printf(TEXT("Team 1 Pickups Left: %i"), Team1)));
        }

    }

    UTextBlock* Widget2 = Cast<UTextBlock>(GetWidgetFromName("TextBlock2"));
    if (Widget2 != nullptr)
    {
        ALab6GameMode* GM = Cast<ALab6GameMode>(GetWorld()->GetAuthGameMode());

        if (GM)
        {
            Team2 = GM->GetTeam2PickupsLeft();

            Widget2->SetText(FText::FromString(FString::Printf(TEXT("Team 1 Pickups Left: %i"), Team2)));
        }

    }
}