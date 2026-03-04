#include "SWS_AudioManager.h"

#include "AI/NavigationSystemBase.h"
#include "Components/AudioComponent.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

ASWS_AudioManager* ASWS_AudioManager::instance;
int ASWS_AudioManager::GroupCount;
FAudioHandle ASWS_AudioManager::NullHandle;

// Matching
ASWS_AudioManager::ASWS_AudioManager(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer), audioHandlePool(), SoundList(), currentlyPlayingAudio()
{
	PrimaryActorTick.bCanEverTick = true;
}

// TODO Not matching
void ASWS_AudioManager::BeginPlay()
{
	Super::BeginPlay();

	LoadAudioData();
}

// Matching
void ASWS_AudioManager::StopAudioByID(int32 id) 
{
	if (currentlyPlayingAudio.Num())
	{
		FAudioHandle** AudioHandle = currentlyPlayingAudio.FindByPredicate([&](FAudioHandle* Handle)
		{
			return Handle->AudioData.AudioID == id;
		});

		if (AudioHandle)
		{
			StopAudioByHandle(**AudioHandle);
		}
	}
}

// Matching
void ASWS_AudioManager::StopAudioByHandle(const FAudioHandle& audioHandle)
{
	if (currentlyPlayingAudio.Num())
	{
		FAudioHandle** AudioHandle = currentlyPlayingAudio.FindByPredicate([&](FAudioHandle* Handle)
		{
			UAudioComponent* audioComponent = audioHandle.AudioComponent;
			return Handle->AudioComponent == audioComponent;
		});
		
		if (AudioHandle)
		{
			(*AudioHandle)->AudioComponent->Stop();
			audioHandlePool.Add(*AudioHandle);
			currentlyPlayingAudio.Remove(*AudioHandle);
		}
	}
}

// Matching
void ASWS_AudioManager::StopAudioByAsset(USoundBase* Base) 
{
	if (currentlyPlayingAudio.Num() && Base)
	{
		FAudioHandle** AudioHandle = currentlyPlayingAudio.FindByPredicate([&](FAudioHandle* Handle)
		{
			return Handle->AudioData.SoundCue == Base;
		});

		if (AudioHandle)
		{
			StopAudioByHandle(**AudioHandle);
		}
	}
}

// Matching
void ASWS_AudioManager::RefreshAudioHandlePool(FAudioHandle& handle) 
{
	audioHandlePool.Add(&handle);
	currentlyPlayingAudio.Remove(&handle);
}

// Matching
FAudioHandle& ASWS_AudioManager::PlayAudioByName(FString Name, const UObject* WorldContextObject, FVector Location, FRotator Rotation, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundAttenuation* AttenuationSettings, USoundConcurrency* ConcurrencySettings, bool bAutoDestroy)
{
	if (SoundList.Num() && !Name.IsEmpty())
	{
		FAudioData** AudioData = SoundList.FindByPredicate([&](FAudioData* Data)
		{
			return Data->name == Name;
		});

		return PlayAudioByAudioData(AudioData, WorldContextObject, Location, Rotation, VolumeMultiplier,
			PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings, bAutoDestroy);
	}
	return NullHandle;
}

// Matching
FAudioHandle& ASWS_AudioManager::PlayAudioByID(int32 ID, const UObject* WorldContextObject, FVector Location, FRotator Rotation, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundAttenuation* AttenuationSettings, USoundConcurrency* ConcurrencySettings, bool bAutoDestroy) 
{
	if (!SoundList.Num())
		return NullHandle;

	FAudioData** AudioData = SoundList.FindByPredicate([&](FAudioData* Data)
	{
		return Data->AudioID == ID;
	});

	return PlayAudioByAudioData(AudioData, WorldContextObject, Location, Rotation, VolumeMultiplier,
		PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings, bAutoDestroy);
}

// Matching
FAudioHandle& ASWS_AudioManager::PlayAudioByAudioData(FAudioData** FoundEntry, const UObject* WorldContextObject, FVector Location, FRotator Rotation, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundAttenuation* AttenuationSettings, USoundConcurrency* ConcurrencySettings, bool bAutoDestroy)
{
	if (FoundEntry)
	{
		FAudioHandle* AudioHandle;

		if (!audioHandlePool.Num())
		{
			AudioHandle = new FAudioHandle;
			audioHandlePool.Add(AudioHandle);
		}
		else
		{
			AudioHandle = audioHandlePool.Top();
		}

		AudioHandle->AudioComponent = UGameplayStatics::SpawnSoundAtLocation(WorldContextObject, (*FoundEntry)->SoundCue, 
			Location, Rotation, VolumeMultiplier, PitchMultiplier, StartTime, 
			AttenuationSettings, ConcurrencySettings, bAutoDestroy);

		currentlyPlayingAudio.Add(AudioHandle);
	
		return *AudioHandle;
	}
	return NullHandle;
}

// Matching
FAudioHandle& ASWS_AudioManager::PlayAudioByAsset(const UObject* WorldContextObject, USoundBase* Sound, FVector Location, FRotator Rotation, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundAttenuation* AttenuationSettings, USoundConcurrency* ConcurrencySettings, bool bAutoDestroy)
{
	if (SoundList.Num() && Sound)
	{
		FAudioData** AudioData = SoundList.FindByPredicate([&](FAudioData* Data)
		{
			return Data->SoundCue == Sound;
		});

		return PlayAudioByAudioData(AudioData, WorldContextObject, Location, Rotation, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings, bAutoDestroy);
	}
	return NullHandle;
}

// Matching
int32 ASWS_AudioManager::GetSoundID(USoundCue* cue) 
{
	if (!SoundList.Num())
		return 0;
	if (!cue)
		return 0;
	
	FAudioData** AudioData = SoundList.FindByPredicate([&](FAudioData* Data)
	{
		return Data->SoundCue == cue;
	});

	if (AudioData)
	{
		return (*AudioData)->AudioID;
	}
	return 0;
}

// Matching
USoundCue* ASWS_AudioManager::GetSoundCueByName(FString Name)
{
	for (int i = 0; i != SoundList.Num(); i++)
	{
		if (SoundList[i]->name == Name)
			return SoundList[i]->SoundCue;
	}
	return nullptr;
}

// Matching
USoundCue* ASWS_AudioManager::GetSoundByID(int32 ID) 
{
	for (int i = 0; i != SoundList.Num(); i++)
	{
		if (SoundList[i]->AudioID == ID)
			return SoundList[i]->SoundCue;
	}
	return nullptr;
}

// TODO Not matching, CompactInvocationList inlined 
ASWS_AudioManager* ASWS_AudioManager::GetAudioManager(UObject* WorldContextObject) 
{
	if (!instance)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert);
		instance = (ASWS_AudioManager*)World->SpawnActor(StaticClass());
		instance->OnAudioManagerSpawned.Broadcast(instance);
	}
	return instance;
}
