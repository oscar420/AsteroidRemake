// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AsteroidRemake : ModuleRules
{
	public AsteroidRemake(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}
