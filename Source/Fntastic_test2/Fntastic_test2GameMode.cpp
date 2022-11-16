// Copyright Epic Games, Inc. All Rights Reserved.

#include "Fntastic_test2GameMode.h"
#include "Fntastic_test2HUD.h"
#include "Fntastic_test2Character.h"
#include "UObject/ConstructorHelpers.h"

AFntastic_test2GameMode::AFntastic_test2GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFntastic_test2HUD::StaticClass();
}
