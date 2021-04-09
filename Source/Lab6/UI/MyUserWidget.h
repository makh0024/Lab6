// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class LAB6_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual bool Initialize() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void DisplayPickupsLeft();

	int Team1;
	int Team2;
};
