// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectRogue2GameMode.h"
#include "ProjectRogue2HUD.h"
#include "ProjectRogue2Character.h"
#include "UObject/ConstructorHelpers.h"

AProjectRogue2GameMode::AProjectRogue2GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AProjectRogue2HUD::StaticClass();
}
