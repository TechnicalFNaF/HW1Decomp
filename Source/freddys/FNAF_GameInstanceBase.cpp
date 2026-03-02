#include "FNAF_GameInstanceBase.h"

#include "UserWidget.h"
#include "ViveportDLC.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "MoviePlayer/Public/MoviePlayer.h"

bool UFNAF_GameInstanceBase::ViveportDLCValid = false;
UFNAF_GameInstanceBase* UFNAF_GameInstanceBase::Instance = nullptr;

constexpr EFNAFGameType GetFNAFGameType()
{
	return EFNAFGameType::Normal;
}
constexpr bool IsDemoMode()
{
	return GetFNAFGameType() == EFNAFGameType::Demo;
}

void UFNAF_GameInstanceBase::MyInitCallback::OnSuccess()
{
	FString fstring("Viveport Init success.");
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}
void UFNAF_GameInstanceBase::MyInitCallback::OnFailure(int error_code)
{
	FString fstring = FString::Printf(TEXT("Viveport Init failure. error=%d"), error_code);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UFNAF_GameInstanceBase::MyShutdownCallback::OnSuccess()
{
	FString fstring("Viveport Shutdown success.");
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UFNAF_GameInstanceBase::MyShutdownCallback::OnFailure(int error_code)
{
	FString fstring = FString::Printf(TEXT("Viveport Shutdown failure. error=%d"), error_code);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UFNAF_GameInstanceBase::MyDLCInitCallback::OnSuccess()
{
	FString fstring("DLC Viveport Init success.");
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

	if (Instance)
	{
		UViveportDLC::IsReady(Instance->GetISDLCReadyCallback());
	}
	else
	{
		FString debugstring = FString::Printf(TEXT("Failed to get game instance."));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
	}
}
void UFNAF_GameInstanceBase::MyDLCInitCallback::OnFailure(int error_code)
{
	FString fstring = FString::Printf(TEXT("DLC Viveport Init failure. error=%d"), error_code);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UFNAF_GameInstanceBase::MyDLCShutdownCallback::OnSuccess()
{
	FString debugstring("DLC Viveport Shutdown success.");
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, debugstring);
}
void UFNAF_GameInstanceBase::MyDLCShutdownCallback::OnFailure(int error_code)
{
	FString fstring = FString::Printf(TEXT("DLC Viveport Shutdown failure. error=%d"), error_code);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UFNAF_GameInstanceBase::MyIsDLCReadyCallback::OnSuccess()
{
	FString debugstring = FString::Printf(TEXT("DLC Viveport Is ready success"));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, debugstring);

	// Get DLC count
	int Count = UViveportDLC::GetCount();
	debugstring = FString::Printf(TEXT("GetDLCCount: %d"), Count);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, debugstring);

	// Get DLC data by index
	static FString dlcAppId = Instance->DLC_APP_ID;
	static bool isAvailable = false;
	bool isIndexZeroInRange = UViveportDLC::GetIsAvailable(0, dlcAppId, isAvailable);
	if (isIndexZeroInRange)
	{
		Instance->InstalledDLCList.Add(EFNAFDLCType::Halloween);
		
		bool DLCValid = ViveportDLCValid;
		if (isAvailable)
			DLCValid = true;
		ViveportDLCValid = DLCValid;
		
		debugstring = FString::Printf(TEXT("DLC App ID: %s, Is available: %s"),
			*dlcAppId,
			isAvailable ? TEXT("true") : TEXT("false"));
	}
	else
	{
		debugstring = FString::Printf(TEXT("Index zero is not in range"));
	}

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, debugstring);
}

void UFNAF_GameInstanceBase::MyIsDLCReadyCallback::OnFailure(int error_code)
{
	FString fstring = FString::Printf(TEXT("IsReady failure. Code = %d"), error_code);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UFNAF_GameInstanceBase::MyLicenseChecker::OnSuccess(long long issue_time, long long expiration_time,
	int latest_version, bool update_required)
{
	// Inaccurate - original game does not use TEXT
	FString debugstring = FString::Printf(TEXT("Verify OK!\n issue_time=%lld,\n expiration_time=%lld,\n latest_version=%d,\n update_required=%d"),
		issue_time,
		expiration_time,
		latest_version,
		update_required);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, debugstring);
}

void UFNAF_GameInstanceBase::MyLicenseChecker::OnFailure(int errorCode, const FString& errorMessage)
{
	// Inaccurate - original game does not use TEXT
	FString fstring = FString::Printf(TEXT("Verify failed!\n error_code=%d,\n error_message=%s"),
		errorCode,
		*errorMessage);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

bool UFNAF_GameInstanceBase::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar)
{
	// does nothing in shipping, probably had debug functions or something
	return Super::Exec(InWorld, Cmd, Ar);
}

int32 UFNAF_GameInstanceBase::GetForcedVariantNumber() const 
{
	return -1;
}

FString UFNAF_GameInstanceBase::GetGPUBrandName()
{
	return FPlatformMisc::GetPrimaryGPUBrand();
}

EFNAFGameType UFNAF_GameInstanceBase::GetGameType() const 
{
	return GetFNAFGameType();
}

FString UFNAF_GameInstanceBase::GetPrimaryGPUBrand() // probably intended to say GetPrimaryCPUBrand
{
	return FPlatformMisc::GetCPUBrand();
}

bool UFNAF_GameInstanceBase::GetViveportDLCValid() const 
{
	return ViveportDLCValid;
}

bool UFNAF_GameInstanceBase::HasDLC(EFNAFDLCType DLC) const 
{
	if (DLC == EFNAFDLCType::BaseGame)
		return true;

	if (InstalledDLCList.Contains(DLC))
		return ViveportDLCValid;

	return false;
}

void UFNAF_GameInstanceBase::Init()
{
	Instance = this;
	Super::Init();

	FString fstring = UViveportApi::Version();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

	UViveportApi::GetLicense(&myLicenseChecker, VIVEPORT_ID, VIVEPORT_KEY);
	UViveportApi::Init(&myInitCallback, VIVEPORT_ID);
	UViveportApi::Init(&myDLCInitCallback, VIVEPORT_ID);

	MountDLC();
}

void UFNAF_GameInstanceBase::MountDLC()
{
	InstalledDLCList.Add(EFNAFDLCType::BaseGame);
}

bool UFNAF_GameInstanceBase::IsInDemoMode() const
{
	return IsDemoMode();
}

void UFNAF_GameInstanceBase::LoadLevelAsync(const FName& LevelName)
{
	if (*LoadingWidget)
	{
		UUserWidget* WidgetInstance = CreateWidget(this, LoadingWidget);
		InstancedLoadingWidget = WidgetInstance;

		FLoadingScreenAttributes LoadingScreen{};

		TSharedRef<SWidget> SlateWidget = WidgetInstance->TakeWidget();
		LoadingScreen.WidgetLoadingScreen = SlateWidget;

		IGameMoviePlayer* MoviePlayer = GetMoviePlayer();
		MoviePlayer->SetupLoadingScreen(LoadingScreen);
	}

	// useless line of code, todo remove 
	FString LongName = LevelName.ToString();

	UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}

// todo find better place for this probably
struct FSaveGameTask : FNonAbandonableTask
{
	USaveGame* SaveGameToStore;
	FString SlotNameToStore;
	int UserIndexToStore;

	FSaveGameTask(USaveGame* InSaveGameToStore, const FString& InSlotNameToStore, int InUserIndexToStore)
		: SaveGameToStore(InSaveGameToStore), SlotNameToStore(InSlotNameToStore), UserIndexToStore(InUserIndexToStore)
	{
	}
	
	void DoWork()
	{
		UGameplayStatics::SaveGameToSlot(SaveGameToStore, SlotNameToStore, UserIndexToStore);
	}
	
	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FSaveGameTask, STATGROUP_ThreadPoolAsyncTasks);
	}
};

void UFNAF_GameInstanceBase::StartAsyncSaveGame(USaveGame* SaveGame, const FString& SlotName, int32 UserIndex)
{
	auto AsyncTask = new FAutoDeleteAsyncTask<FSaveGameTask>(SaveGame, SlotName, UserIndex);
	AsyncTask->StartBackgroundTask();
}

void UFNAF_GameInstanceBase::SwitchFNAFGameType(EFNAFGameType& GameType)
{
	GameType = GetFNAFGameType();
}
