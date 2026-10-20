#include "FreddysPakPlatformFile.h"

#include "CommandLine.h"
#include "CoreDelegates.h"
#include "Editor.h"
#include "freddysEditor.h"
#include "PackageName.h"
#include "PlatformFilemanager.h"

#ifndef ALL_PAKS_WILDCARD
	#define ALL_PAKS_WILDCARD "*.pak"
#endif 

#ifndef MOUNT_STARTUP_PAKS_WILDCARD
	#define MOUNT_STARTUP_PAKS_WILDCARD ALL_PAKS_WILDCARD
#endif

static const FString PakFolder = TEXT("C:\\Program Files (x86)\\Steam\\steamapps\\common\\FNAFVRHelpWanted\\freddys\\Content\\Paks");

void FFreddysPakPlatformFile::OnFEngineLoopInitComplete()
{
	// Currently broken FPackageName::RegisterMountPoint(TEXT("/Game/"), TEXT("../../../freddys/Content/"));
	//FPackageName::RegisterMountPoint(TEXT("/Game/Audio/"), TEXT("../../../freddys/Content/Audio"));

	FPackageName::RegisterMountPoint(TEXT("/HalloweenDLC/"), TEXT("../../../freddys/Plugins/HalloweenDLC/Content/"));

	ListRootFolders();
}

bool FFreddysPakPlatformFile::Initialize(IPlatformFile* Inner, const TCHAR* CommandLineParam)
{
	LLM_SCOPE(ELLMTag::FileSystem);
	SCOPED_BOOT_TIMING("FFreddysPakPlatformFile::Initialize");
	// Inner is required.
	check(Inner != NULL);
	SetLowerLevel(Inner);
	
	// Find and mount pak files from the specified directories.
	TArray<FString> PakFolders {
		PakFolder,
	};
	
	const int32 MountedPaks = MountAllPakFiles(PakFolders, TEXT(MOUNT_STARTUP_PAKS_WILDCARD));
	UE_LOG(LogFreddysEditor, Display, TEXT("Mounted %d pak(s) from '%s'"), MountedPaks, *PakFolder);
	
	FCoreDelegates::OnMountAllPakFiles.BindRaw(this, &FPakPlatformFile::MountAllPakFiles);
	//FCoreDelegates::OnMountPak.BindRaw(this, &FPakPlatformFile::HandleMountPakDelegate);
	//FCoreDelegates::OnUnmountPak.BindRaw(this, &FPakPlatformFile::HandleUnmountPakDelegate);
	FCoreDelegates::OnOptimizeMemoryUsageForMountedPaks.BindRaw(this, &FPakPlatformFile::OptimizeMemoryUsageForMountedPaks);
	
	FCoreDelegates::OnFEngineLoopInitComplete.AddRaw(this, &FPakPlatformFile::OptimizeMemoryUsageForMountedPaks);

	// Load all content when engine loop is done
	FCoreDelegates::OnFEngineLoopInitComplete.AddRaw(this, &FFreddysPakPlatformFile::OnFEngineLoopInitComplete);

	return true;
}