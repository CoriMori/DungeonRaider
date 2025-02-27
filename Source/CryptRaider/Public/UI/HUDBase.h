// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Components/WidgetComponent.h"
#include "UI/WidgetBase.h"
#include "HUDBase.generated.h"

//Basic HUD class -> Used in RaiderPlayerState to update Score value
UCLASS()
class CRYPTRAIDER_API AHUDBase : public AHUD
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	virtual void DrawHUD() override;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UWidgetBase> ScoreWidgetClass;

	void OnScoreChanged(int32 Score);

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UWidgetBase> ScoreWidget;
private:

};
