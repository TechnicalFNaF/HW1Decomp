#include "SWS_AudioSource.h"

#include "SWS_AudioManager.h"
#include "Components/AudioComponent.h"

ASWS_AudioSource::ASWS_AudioSource(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer) 
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASWS_AudioSource::StopAudio(UObject* WorldContextObject) 
{
	ASWS_AudioManager* AudioManager = ASWS_AudioManager::GetAudioManager(this);
	AudioManager->StopAudioByAsset(SoundCueFile);
}

void ASWS_AudioSource::PlayAudio(const UObject* WorldContextObject, USoundBase* Sound, FVector Location, FRotator Rotation, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundAttenuation* AttenuationSettings, USoundConcurrency* ConcurrencySettings, bool bAutoDestroy) 
{
    ASWS_AudioManager* AudioManager = ASWS_AudioManager::GetAudioManager(this);

    FAudioHandle AudioHandle = AudioManager->PlayAudioByAsset(WorldContextObject, Sound, Location, Rotation, VolumeMultiplier, PitchMultiplier,StartTime,
        AttenuationSettings, ConcurrencySettings, bAutoDestroy);

	AudioHandle.AudioComponent->OnAudioFinished.AddDynamic(this, &ASWS_AudioSource::DestroyHandle);
}

void ASWS_AudioSource::DestroyHandle() 
{
	ASWS_AudioManager* AudioManager = ASWS_AudioManager::GetAudioManager(this);
	AudioManager->StopAudioByHandle(*AudioHandle);
}