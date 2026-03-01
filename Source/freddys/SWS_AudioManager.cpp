#include "SWS_AudioManager.h"

ASWS_AudioManager::ASWS_AudioManager(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->AudioAssetData = NULL;
}

void ASWS_AudioManager::StopAudioByID(int32 ID) {
}

void ASWS_AudioManager::StopAudioByHandle(const FAudioHandle& AudioHandle) {
}

void ASWS_AudioManager::StopAudioByAsset(USoundBase* Base) {
}

void ASWS_AudioManager::RefreshAudioHandlePool(FAudioHandle& Handle) {
}

FAudioHandle ASWS_AudioManager::PlayAudioByName(const FString& Name, const UObject* WorldContextObject, FVector Location, FRotator Rotation, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundAttenuation* AttenuationSettings, USoundConcurrency* ConcurrencySettings, bool bAutoDestroy) {
    return FAudioHandle{};
}

FAudioHandle ASWS_AudioManager::PlayAudioByID(int32 ID, const UObject* WorldContextObject, FVector Location, FRotator Rotation, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundAttenuation* AttenuationSettings, USoundConcurrency* ConcurrencySettings, bool bAutoDestroy) {
    return FAudioHandle{};
}

FAudioHandle ASWS_AudioManager::PlayAudioByAsset(const UObject* WorldContextObject, USoundBase* Sound, FVector Location, FRotator Rotation, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundAttenuation* AttenuationSettings, USoundConcurrency* ConcurrencySettings, bool bAutoDestroy) {
    return FAudioHandle{};
}

int32 ASWS_AudioManager::GetSoundID(USoundCue* cue) {
    return 0;
}

USoundCue* ASWS_AudioManager::GetSoundCueByName(const FString& Name) {
    return NULL;
}

USoundCue* ASWS_AudioManager::GetSoundByID(int32 ID) {
    return NULL;
}

ASWS_AudioManager* ASWS_AudioManager::GetAudioManager(UObject* WorldContextObject) {
    return NULL;
}


