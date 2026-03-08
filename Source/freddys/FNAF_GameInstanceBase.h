#pragma once
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FNAF_Collectables.h"
#include "ViveportApi.h"

#include "FNAF_GameInstanceBase.generated.h"

UENUM()
enum class EFNAFDLCType : uint8
{
	BaseGame,
	Halloween
};

class USaveGame;
class UUserWidget;



UCLASS(NonTransient)
class FREDDYS_API UFNAF_GameInstanceBase : public UGameInstance
{
	GENERATED_BODY()
	
	EFNAFGameType GetFNAFGameType() const;
	bool IsDemoMode() const;

public:
	// TODO wrap these with TEXT()
	FString VIVEPORT_ID = "8bdd0597-0591-4b01-8051-0bd9382bc552";
	FString VIVEPORT_KEY = "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQCgni4MT6/xNmZm1WRU3b9fOSTb+2NDyzCdYKwArcM2a8MXr4wssMu1TfY8q+2N98bRbmcCvLqG+UkJKE64IuzppBzhS7DDtA7I/ONu0aUpjnjCFoqwl8pH7uE8Bw2W0MwV+WoC+s+QzPQqwJes2CcqB53deOng+hvANNrlgS5m0QIDAQAB";
	FString DLC_APP_ID = "4e17c449-c278-4acb-89bb-cc85f7ebf90f";

private:
	class MyInitCallback : public ViveportApiStatus
	{
	public:
		void OnSuccess(
			) override;
		void OnFailure(int error_code
			) override;
	};
	MyInitCallback myInitCallback;

	class MyShutdownCallback : public ViveportApiStatus
	{
	public:
		void OnSuccess(
			) override;
		void OnFailure(int error_code
			) override;
	};
	MyShutdownCallback myShutdownCallback;
	
	class MyDLCInitCallback : public ViveportApiStatus
	{
	public:
		void OnSuccess(
		) override;
		void OnFailure(int error_code
		) override;
	};
	MyDLCInitCallback myDLCInitCallback;
	
	class MyDLCShutdownCallback : public ViveportApiStatus
	{
	public:
		void OnSuccess(
		) override;
		void OnFailure(int error_code
		) override;
	};
	MyDLCShutdownCallback myDLCShutdownCallback;

	class MyIsDLCReadyCallback : public ViveportApiStatus
	{
	public:
		void OnSuccess(
		) override;
		void OnFailure(int error_code
		) override;
	};
	MyIsDLCReadyCallback myIsDLCReadyCallback;
	
	class MyLicenseChecker : public UViveportApi::LicenseChecker
	{
	public:
		void OnSuccess(
				long long issue_time,
				long long expiration_time,
				int latest_version,
				bool update_required
		) override;
		void OnFailure(
				int errorCode,
				const FString& errorMessage
		) override;
	};
	MyLicenseChecker myLicenseChecker;
	
public:

	ViveportApiStatus* GetDLCInitCallback() { return &myDLCInitCallback; }
	ViveportApiStatus* GetDLCShutdownCallback() { return &myDLCShutdownCallback; }
	ViveportApiStatus* GetISDLCReadyCallback() { return &myIsDLCReadyCallback; }
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 ForcedVariantNumber = -1;
	
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LoadingWidget;

	// TODO make this uproperty to avoid stale pointer from gc
	UUserWidget* InstancedLoadingWidget = nullptr;
	
	TArray<EFNAFDLCType> InstalledDLCList;

public:
	bool Exec(class UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;

	// Matching
	UFUNCTION(BlueprintPure)
	int32 GetForcedVariantNumber() const
	{
		return -1;
	}
	
	UFUNCTION(BlueprintPure)
	static FString GetGPUBrandName();

	// Matching
	UFUNCTION(BlueprintPure)
	EFNAFGameType GetGameType() const
	{
		return GetFNAFGameType();
	}
	
	UFUNCTION(BlueprintPure)
	static FString GetPrimaryGPUBrand();

	static bool ViveportDLCValid;
	
	// Matching
	UFUNCTION(BlueprintPure)
	bool GetViveportDLCValid() const
	{
		return ViveportDLCValid;
	}
	
	static UFNAF_GameInstanceBase* Instance;

	UFUNCTION(BlueprintPure)
	bool HasDLC(EFNAFDLCType DLC) const;


	virtual void Init() override;
	void MountDLC();

	UFUNCTION(BlueprintCallable)
	void LoadLevelAsync(const FName& LevelName);
	
	// Matching
	UFUNCTION(BlueprintCallable, meta=(ExpandEnumAsExecs="GameType"))
	void SwitchFNAFGameType(EFNAFGameType& GameType)
	{
		GameType = GetFNAFGameType();
	}
	
	UFUNCTION(BlueprintCallable)
	void StartAsyncSaveGame(USaveGame* SaveGame, const FString& SlotName, int32 UserIndex);

	// Matching
	UFUNCTION(BlueprintPure)
	bool IsInDemoMode() const
	{
		return IsDemoMode();
	}
};
