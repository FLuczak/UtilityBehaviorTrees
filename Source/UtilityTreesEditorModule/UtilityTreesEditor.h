#pragma once

#include "Modules/ModuleManager.h"

class FUtilityTreesEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};