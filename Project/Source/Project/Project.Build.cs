// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class Project : ModuleRules
{
    public Project(ReadOnlyTargetRules Target) : base(Target)
    {   
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        #region Path Setting
        PublicIncludePaths.AddRange(new string[] { "Project" });
        #endregion

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" , "NavigationSystem", "AIModule", "GameplayTasks", "UMG" });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
