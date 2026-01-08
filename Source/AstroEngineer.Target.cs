// Copyright Astro Engineer Team. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class AstroEngineerTarget : TargetRules
{
	public AstroEngineerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;
		ExtraModuleNames.Add("AstroEngineer");
	}
}
