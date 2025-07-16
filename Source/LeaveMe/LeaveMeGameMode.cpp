// Copyright Epic Games, Inc. All Rights Reserved.

#include "LeaveMeGameMode.h"
#include "LeaveMeCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALeaveMeGameMode::ALeaveMeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
