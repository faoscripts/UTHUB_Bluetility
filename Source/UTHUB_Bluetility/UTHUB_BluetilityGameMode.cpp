// Copyright Epic Games, Inc. All Rights Reserved.

#include "UTHUB_BluetilityGameMode.h"
#include "UTHUB_BluetilityCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUTHUB_BluetilityGameMode::AUTHUB_BluetilityGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
