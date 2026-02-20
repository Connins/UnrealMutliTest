// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ConnorJam : ModuleRules
{
	public ConnorJam(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"ConnorJam",
			"ConnorJam/Variant_Platforming",
			"ConnorJam/Variant_Platforming/Animation",
			"ConnorJam/Variant_Combat",
			"ConnorJam/Variant_Combat/AI",
			"ConnorJam/Variant_Combat/Animation",
			"ConnorJam/Variant_Combat/Gameplay",
			"ConnorJam/Variant_Combat/Interfaces",
			"ConnorJam/Variant_Combat/UI",
			"ConnorJam/Variant_SideScrolling",
			"ConnorJam/Variant_SideScrolling/AI",
			"ConnorJam/Variant_SideScrolling/Gameplay",
			"ConnorJam/Variant_SideScrolling/Interfaces",
			"ConnorJam/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
