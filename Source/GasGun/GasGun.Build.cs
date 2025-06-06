// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GasGun : ModuleRules
{
	public GasGun(ReadOnlyTargetRules Target) : base(Target)
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
			"GameplayAbilities", 
			"GameplayTasks", 
			"GameplayTags",
			"NavigationSystem",
			"Niagara",
			"NetCommon",
			"Networking",
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"GasGun",
			"GasGun/AbilitySystem",
			"GasGun/AbilitySystem/Abilities",
			"GasGun/AbilitySystem/AttributeSets",
			"GasGun/AbilitySystem/Data",
			"GasGun/AbilitySystem/EffectCalculations",
			"GasGun/AbilitySystem/Effects",
			"GasGun/AbilitySystem/Tasks",
			"GasGun/Characters",
			"GasGun/Guns",
			"GasGun/Projectiles",
			"GasGun/Variant_Horror",
			"GasGun/Variant_Shooter",
			"GasGun/Variant_Shooter/AI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
