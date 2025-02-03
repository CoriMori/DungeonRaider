// Fill out your copyright notice in the Description page of Project Settings.


#include "RaiderPlayerState.h"
#include "HUDBase.h"

ARaiderPlayerState::ARaiderPlayerState()
{
}

void ARaiderPlayerState::SetPlayerScore(int32 newScore)
{
	playerScore = newScore;
	Cast<AHUDBase>(GetPlayerController()->GetHUD())->OnScoreChanged(playerScore); // broadcast event on the widget
}
