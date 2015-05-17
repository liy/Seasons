// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Seasons.h"
#include "SeasonsGameMode.h"
#include "SeasonsPlayerController.h"
#include "SeasonsCharacter.h"

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
}