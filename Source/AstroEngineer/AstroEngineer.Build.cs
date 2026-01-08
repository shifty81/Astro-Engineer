// Copyright Astro Engineer Team. All Rights Reserved.

using UnrealBuildTool;

public class AstroEngineer : ModuleRules
{
	public AstroEngineer(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"EnhancedInput",
			"UMG",
			"Slate",
			"SlateCore"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { 
			"AIModule"
		});
	}
}
