// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AnimationTest : ModuleRules
{
	public AnimationTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] {
												"Core", 
												"CoreUObject", 
												"ApplicationCore",
												"Engine", 
												"InputCore", 
												"SNPlugin",
												"StateTreeModule",
												"OnlineSubsystem",
												"OnlineSubsystemUtils",
												"EnhancedInput" 
											}
										);

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
