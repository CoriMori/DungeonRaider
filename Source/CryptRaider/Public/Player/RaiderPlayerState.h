// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "RaiderPlayerState.generated.h"

//Basic Playerstate class -> holds player score and updates the HUD when the score is changed
UCLASS()
class CRYPTRAIDER_API ARaiderPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ARaiderPlayerState();

	int32 GetPlayerScore() const { return playerScore; }
	void SetPlayerScore(int32 newScore);

private:
	int32 playerScore = 0;
	
};
