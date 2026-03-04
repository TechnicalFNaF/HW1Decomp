#pragma once
#include "CoreMinimal.h"
#include "ConstructorHelpers.h"
#include "SWS_AudioStatics.h"
#include "GameFramework/Actor.h"
#include "SWS_AudioManager.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAudioManagerSpawned, ASWS_AudioManager*)

UCLASS()
class FREDDYS_API ASWS_AudioManager : public AActor 
{
	GENERATED_BODY()
public:	

	ASWS_AudioManager(const FObjectInitializer& ObjectInitializer);

private:
	UPROPERTY(VisibleAnywhere)
	UDataTable* AudioAssetData;

	static ASWS_AudioManager* instance;
	static int GroupCount;

	TArray<FAudioHandle*> audioHandlePool;
	TArray<FAudioData*> SoundList;
	TArray<FAudioHandle*> currentlyPlayingAudio;

	static FAudioHandle NullHandle;
	FOnAudioManagerSpawned OnAudioManagerSpawned;
	
private:

	// TODO Not matching
	FORCEINLINE void LoadAudioData()
	{
		FString location = "/Game/ProductionAssets/Audio";
		FString sceneName = GetWorld()->GetName();
		location += sceneName + "_AudioAssets";

		static ConstructorHelpers::FObjectFinder<UDataTable> myTable(*location);

		if (myTable.Object)
			AudioAssetData = myTable.Object;

		UDataTable* AudioAsset = AudioAssetData;
		AudioAsset->GetAllRows<FAudioData>("", SoundList);
	}

protected:

	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
	void StopAudioByID(int32 ID);
	
	UFUNCTION(BlueprintCallable)
	void StopAudioByHandle(const FAudioHandle& AudioHandle);
	
	UFUNCTION(BlueprintCallable)
	void StopAudioByAsset(USoundBase* Base);
	
	UFUNCTION(BlueprintCallable)
	void RefreshAudioHandlePool(FAudioHandle& Handle);
	
	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
	FAudioHandle& PlayAudioByName(FString Name, const UObject* WorldContextObject, FVector Location, FRotator Rotation, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundAttenuation* AttenuationSettings, USoundConcurrency* ConcurrencySettings, bool bAutoDestroy);
	
	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
	FAudioHandle& PlayAudioByID(int32 ID, const UObject* WorldContextObject, FVector Location, FRotator Rotation, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundAttenuation* AttenuationSettings, USoundConcurrency* ConcurrencySettings, bool bAutoDestroy);
	
	FAudioHandle& PlayAudioByAudioData(FAudioData** FoundEntry, const UObject* WorldContextObject, FVector Location, FRotator Rotation, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundAttenuation* AttenuationSettings, USoundConcurrency* ConcurrencySettings, bool bAutoDestroy);

	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
	FAudioHandle& PlayAudioByAsset(const UObject* WorldContextObject, USoundBase* Sound, FVector Location, FRotator Rotation, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundAttenuation* AttenuationSettings, USoundConcurrency* ConcurrencySettings, bool bAutoDestroy);
	
	UFUNCTION(BlueprintCallable)
	int32 GetSoundID(USoundCue* cue);
	
	UFUNCTION(BlueprintCallable)
	USoundCue* GetSoundCueByName(FString Name);
	
	UFUNCTION(BlueprintCallable)
	USoundCue* GetSoundByID(int32 ID);
	
	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
	static ASWS_AudioManager* GetAudioManager(UObject* WorldContextObject);
};

