#include "SWS_GroupComponent.h"
#include "SWS_AudioSource.h"
#include "Sound/SoundCue.h"

void USWS_GroupComponent::BeginPlay()
{
	Super::BeginPlay();
}

USWS_GroupComponent::USWS_GroupComponent(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer), ListOfAudioSources()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USWS_GroupComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USWS_GroupComponent::Initialize(int id)
{
	GroupID = id;
	if (!(ListOfAudioSources.Num() <= 0))
	{
		for (ASWS_AudioSource* AudioSource : ListOfAudioSources)
		{
			AudioSource->AudioGroupID = GroupID;
		}
	}
}

void USWS_GroupComponent::UnRegisterAudioSource(ASWS_AudioSource* cue) 
{
	ListOfAudioSources.Remove(cue);
}

void USWS_GroupComponent::RegisterAudioSource(ASWS_AudioSource* cue) 
{
	ListOfAudioSources.Add(cue);
}

void USWS_GroupComponent::OnVolumeModified_Implementation(float Volume) 
{
}

void USWS_GroupComponent::OnPitchModified_Implementation(float Pitch) 
{
}

void USWS_GroupComponent::ModifyGroupVolumeMultiplier(float volumeMultiplier)
{
	for (ASWS_AudioSource* AudioSource : ListOfAudioSources)
	{
		if (AudioSource->AudioHandle)
		{
			AudioSource->SoundCueFile->VolumeMultiplier = volumeMultiplier;
		}
	}

	if (ListOfAudioSources.Num() > 0)
		OnVolumeModified(volumeMultiplier);
}

void USWS_GroupComponent::ModifyGroupPitchMultiplier(float newPitchMultiplier)
{
	for (ASWS_AudioSource* AudioSource : ListOfAudioSources)
	{
		if (AudioSource->AudioHandle)
		{
			AudioSource->SoundCueFile->PitchMultiplier = newPitchMultiplier;
		}
	}

	if (ListOfAudioSources.Num() > 0)
		OnVolumeModified(newPitchMultiplier); // Bug, calling wrong function
}

int32 USWS_GroupComponent::GetTotalFrequency() 
{
	// Possibly unused
	return 0;
}

int32 USWS_GroupComponent::GetTotalAmplitude() 
{
	// Possibly unused
	return 0;
}


