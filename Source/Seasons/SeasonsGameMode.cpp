// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Seasons.h"
#include "SeasonsGameMode.h"
#include "SeasonsPlayerController.h"
#include "SeasonsCharacter.h"
#include "GameFramework/HUD.h"

ASeasonsGameMode::ASeasonsGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// use our custom PlayerController class
	PlayerControllerClass = ASeasonsPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<AHUD> GameHUDClass(TEXT("/Game/TopDown/UI/GameHUD"));
	if (GameHUDClass.Class != NULL)
	{
		HUDClass = GameHUDClass.Class;
	}
}