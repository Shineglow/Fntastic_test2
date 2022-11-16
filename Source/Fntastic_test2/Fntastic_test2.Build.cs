// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Fntastic_test2 : ModuleRules
{
	public Fntastic_test2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
