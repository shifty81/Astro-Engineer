// Copyright Astro Engineer Team. All Rights Reserved.

#include "AstroGameMode.h"
#include "AstroPlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAstroGameMode::AAstroGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = AAstroPlayerCharacter::StaticClass();
}
