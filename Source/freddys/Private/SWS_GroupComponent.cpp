#include "SWS_GroupComponent.h"

USWS_GroupComponent::USWS_GroupComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
}

void USWS_GroupComponent::UnRegisterAudioSource(ASWS_AudioSource* cue) {
}

void USWS_GroupComponent::RegisterAudioSource(ASWS_AudioSource* cue) {
}

void USWS_GroupComponent::OnVolumeModified_Implementation(float Volume) {
}

void USWS_GroupComponent::OnPitchModified_Implementation(float Pitch) {
}

void USWS_GroupComponent::ModifyGroupVolumeMultiplier(float Volume) {
}

void USWS_GroupComponent::ModifyGroupPitchMultiplier(float Pitch) {
}

int32 USWS_GroupComponent::GetTotalFrequency() {
    return 0;
}

int32 USWS_GroupComponent::GetTotalAmplitude() {
    return 0;
}


