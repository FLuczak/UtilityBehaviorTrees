// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UtilityTreesEditor : ModuleRules
{
    public UtilityTreesEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "AIModule" });

        PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "UnrealEd", "AssetTools","UtilityTrees", "BehaviorTreeEditor", // Needed for FAssetTypeActions_BehaviorTree
        "AssetTools",
        "UnrealEd", // Required for asset registration
        "EditorStyle",
        "BlueprintGraph",
        "AssetDefinition",
        "AIGraph", 
        "Slate",
        "SlateCore"
            });

        PublicIncludePaths.AddRange(new string[] {
            "UtilityTreesEditorModule/Public"
        });

        PrivateIncludePaths.AddRange(new string[] {
            "UtilityTreesEditorModule/Private"
        });

        PublicIncludePaths.AddRange(new string[] {
            "UtilityTreesEditorModule"
        });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
