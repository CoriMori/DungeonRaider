// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player/CryptRaiderGameMode.h"
#include "Player/CryptRaiderCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACryptRaiderGameMode::ACryptRaiderGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
