// Copyright Astro Engineer Team. All Rights Reserved.

#include "AstroEngineer.h"
#include "Modules/ModuleManager.h"

void FAstroEngineerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory
}

void FAstroEngineerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module
}

IMPLEMENT_PRIMARY_GAME_MODULE(FAstroEngineerModule, AstroEngineer, "AstroEngineer");
