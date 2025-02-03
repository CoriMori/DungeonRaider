// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDBase.h"

void AHUDBase::BeginPlay()
{
	Super::BeginPlay();

	if (ScoreWidgetClass) {
		ScoreWidget = CreateWidget<UWidgetBase>(GetWorld(), ScoreWidgetClass);

		if (ScoreWidget) {
			ScoreWidget->AddToViewport();
		}
	}
}

void AHUDBase::DrawHUD()
{
	Super::DrawHUD();
}

void AHUDBase::OnScoreChanged(int32 Score)
{
	if (ScoreWidget) {
		ScoreWidget->OnScoreChanged(Score);
	}
}
