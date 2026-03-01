#pragma once
#include "CoreMinimal.h"
#include "SWS_AudioStatics.h"
#include "GameFramework/Actor.h"
#include "SWS_AudioManager.generated.h"

UCLASS()
class FREDDYS_API ASWS_AudioManager : public AActor 
{
    GENERATED_BODY()
public:
private:
    UPROPERTY(VisibleAnywhere)
    UDataTable* AudioAssetData;
    
public:
    ASWS_AudioManager(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void StopAudioByID(int32 ID);
    
    UFUNCTION(BlueprintCallable)
    void StopAudioByHandle(const FAudioHandle& AudioHandle);
    
    UFUNCTION(BlueprintCallable)
    void StopAudioByAsset(USoundBase* Base);
    
    UFUNCTION(BlueprintCallable)
    void RefreshAudioHandlePool(FAudioHandle& Handle);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    FAudioHandle PlayAudioByName(const FString& Name, const UObject* WorldContextObject, FVector Location, FRotator Rotation, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundAttenuation* AttenuationSettings, USoundConcurrency* ConcurrencySettings, bool bAutoDestroy);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    FAudioHandle PlayAudioByID(int32 ID, const UObject* WorldContextObject, FVector Location, FRotator Rotation, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundAttenuation* AttenuationSettings, USoundConcurrency* ConcurrencySettings, bool bAutoDestroy);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    FAudioHandle PlayAudioByAsset(const UObject* WorldContextObject, USoundBase* Sound, FVector Location, FRotator Rotation, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundAttenuation* AttenuationSettings, USoundConcurrency* ConcurrencySettings, bool bAutoDestroy);
    
    UFUNCTION(BlueprintCallable)
    int32 GetSoundID(USoundCue* cue);
    
    UFUNCTION(BlueprintCallable)
    USoundCue* GetSoundCueByName(const FString& Name);
    
    UFUNCTION(BlueprintCallable)
    USoundCue* GetSoundByID(int32 ID);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static ASWS_AudioManager* GetAudioManager(UObject* WorldContextObject);
};

