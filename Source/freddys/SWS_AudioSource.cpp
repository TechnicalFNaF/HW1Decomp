#include "SWS_AudioSource.h"

#include "SWS_AudioManager.h"
#include "Components/AudioComponent.h"

// Matching
ASWS_AudioSource::ASWS_AudioSource()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Matching
void ASWS_AudioSource::StopAudio(UObject* WorldContextObject) 
{
	ASWS_AudioManager* AudioManager = ASWS_AudioManager::GetAudioManager(this);
	AudioManager->StopAudioByAsset(SoundCueFile);
}

// Matching
void ASWS_AudioSource::PlayAudio(const UObject* WorldContextObject, USoundBase* Sound, FVector Location,
	FRotator Rotation, float VolumeMultiplier, float PitchMultiplier, float StartTime,
	USoundAttenuation* AttenuationSettings, USoundConcurrency* ConcurrencySettings, bool bAutoDestroy) 
{
    ASWS_AudioManager* AudioManager = ASWS_AudioManager::GetAudioManager(this);

	FAudioHandle NewAudioHandle = AudioManager->PlayAudioByAsset(WorldContextObject, Sound, Location,
    	Rotation, VolumeMultiplier, PitchMultiplier,StartTime,
        AttenuationSettings, ConcurrencySettings, bAutoDestroy);

	NewAudioHandle.AudioComponent->OnAudioFinished.AddDynamic(this, &ASWS_AudioSource::DestroyHandle);
	AudioHandle = &NewAudioHandle;
}

// Matching
void ASWS_AudioSource::DestroyHandle() 
{
	ASWS_AudioManager* AudioManager = ASWS_AudioManager::GetAudioManager(this);
	AudioManager->StopAudioByHandle(*AudioHandle);
}