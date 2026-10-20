#pragma once
#include "AI/Navigation/NavigationTypes.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFreddysEditor, All, All)

/**
 * NOTE: None of this is original to the game, it is purely additional.
 * This existing does not affect the shipping output as this is editor only.
 * The main purpose is mounting paks in editor.
 */
class freddysEditor : public IModuleInterface
{
public:

	void OnPostEngineInit();
	void GetPakEncryptionKeyDelegate(uint8 OutKey[32]);
	
	//~ Begin IModuleInterface Interface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	//~ End IModuleInterface Interface
};