// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RaiderPlayerState.h"
#include "UI/HUDBase.h"

ARaiderPlayerState::ARaiderPlayerState()
{
}

//Update player score value and then update the HUD
void ARaiderPlayerState::SetPlayerScore(int32 newScore)
{
	playerScore = newScore;
	Cast<AHUDBase>(GetPlayerController()->GetHUD())->OnScoreChanged(playerScore); // broadcast event on the widget
}
