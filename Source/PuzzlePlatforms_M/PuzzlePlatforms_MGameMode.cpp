// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "PuzzlePlatforms_MGameMode.h"
#include "PuzzlePlatforms_MCharacter.h"
#include "UObject/ConstructorHelpers.h"

APuzzlePlatforms_MGameMode::APuzzlePlatforms_MGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
