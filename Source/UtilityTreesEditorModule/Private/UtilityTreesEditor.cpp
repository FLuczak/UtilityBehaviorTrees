#include "UtilityTreesEditor.h"
#include "Modules/ModuleManager.h"
#include "AssetToolsModule.h"
#include "IAssetTools.h"
#include "UtilityBTDetailsCustomization.h"

IMPLEMENT_MODULE(FUtilityTreesEditorModule, UtilityTreesEditor)


void FUtilityTreesEditorModule::StartupModule()
{
}

void FUtilityTreesEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.UnregisterCustomClassLayout("BehaviorTree");
	}
}