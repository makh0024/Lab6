// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Lab6 : ModuleRules
{
	public Lab6(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
