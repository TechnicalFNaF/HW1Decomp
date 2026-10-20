#include "freddysEditor.h"

#include "App.h"
#include "AssetRegistryModule.h"
#include "CoreDelegates.h"
#include "FileManager.h"
#include "FreddysPakPlatformFile.h"
#include "IPlatformFilePak.h"
#include "PlatformFilemanager.h"

IMPLEMENT_MODULE(freddysEditor, freddysEditor)
DEFINE_LOG_CATEGORY(LogFreddysEditor)

// Could use FPakPlatformFile::RegisterEncryptionKey instead
void freddysEditor::GetPakEncryptionKeyDelegate(uint8 OutKey[32])
{
	// Hardcoded key of HW1
	uint8 Key[32] = {
		0x71, 0x08, 0x91, 0xDF, 0x17, 0xEA, 0xFF, 0xCA,
		0x17, 0xCB, 0x06, 0x20, 0xF0, 0xF0, 0xDC, 0xA9,
		0x0A, 0x00, 0xC6, 0x57, 0xF4, 0x9B, 0xC1, 0x31,
		0xD4, 0x11, 0x0B, 0x26, 0x5E, 0xC2, 0xE4, 0x1E
	};

	FMemory::Memcpy(OutKey, Key, sizeof(Key));
}

void freddysEditor::StartupModule()
{
	FCoreDelegates::GetPakEncryptionKeyDelegate().BindRaw(this, &freddysEditor::GetPakEncryptionKeyDelegate);
	FPlatformFileManager& Manager = FPlatformFileManager::Get();
	
	FFreddysPakPlatformFile* PakFileMgr = new FFreddysPakPlatformFile();
	if (!PakFileMgr->Initialize(&Manager.GetPlatformFile(), TEXT("")))
	{
		UE_LOG(LogFreddysEditor, Error, TEXT("Could not set up PakFile platform."));
		return;
	}
	Manager.SetPlatformFile(*PakFileMgr);
}

void freddysEditor::ShutdownModule()
{

}