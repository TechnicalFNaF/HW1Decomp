#include "SWS_AudioSource.h"

ASWS_AudioSource::ASWS_AudioSource(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	this->SoundCueFile = NULL;
}

void ASWS_AudioSource::StopAudio(UObject* WorldContextObject) {
}

void ASWS_AudioSource::PlayAudio(const UObject* WorldContextObject, USoundBase* Sound, FVector Location, FRotator Rotation, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundAttenuation* AttenuationSettings, USoundConcurrency* ConcurrencySettings, bool bAutoDestroy) {
}

void ASWS_AudioSource::DestroyHandle() {
}


