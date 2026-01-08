// Copyright Astro Engineer Team. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class AstroEngineerEditorTarget : TargetRules
{
	public AstroEngineerEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V6;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;
		BuildEnvironment = TargetBuildEnvironment.Unique;
		ExtraModuleNames.Add("AstroEngineer");
	}
}
