#include "SWS_AudioManager.h"

#include "ConstructorHelpers.h"
#include "AI/NavigationSystemBase.h"
#include "Components/AudioComponent.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

ASWS_AudioManager* ASWS_AudioManager::instance;
int ASWS_AudioManager::GroupCount;
FAudioHandle ASWS_AudioManager::NullHandle;

ASWS_AudioManager::ASWS_AudioManager(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer), audioHandlePool(), SoundList(), currentlyPlayingAudio()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASWS_AudioManager::LoadAudioData()
{
	FString location = "/Game/ProductionAssets/Audio";
	FString sceneName = GetWorld()->GetName();
	location += sceneName + "_AudioAssets";

	static ConstructorHelpers::FObjectFinder<UDataTable> myTable(*location);

	if (myTable.Object)
		AudioAssetData = myTable.Object;

	AudioAssetData->GetAllRows<FAudioData>("", SoundList);
}

void ASWS_AudioManager::BeginPlay()
{
	Super::BeginPlay();

	LoadAudioData();
}

void ASWS_AudioManager::StopAudioByID(int32 ID) 
{
	if (currentlyPlayingAudio.Num())
	{
		FAudioHandle* AudioHandle = *currentlyPlayingAudio.FindByPredicate([&](FAudioHandle* AudioHandle)
			{
				return AudioHandle->AudioData.AudioID == ID;
			});

		StopAudioByHandle(*AudioHandle);
	}
}

void ASWS_AudioManager::StopAudioByHandle(const FAudioHandle& audioHandle)
{
	if (currentlyPlayingAudio.Num())
	{
		UAudioComponent* audioComponent = audioHandle.AudioComponent;
		FAudioHandle* AudioHandle = *currentlyPlayingAudio.FindByPredicate([&](FAudioHandle* AudioHandle)
			{
				return AudioHandle->AudioComponent == audioComponent;
			});

		audioHandlePool.Add(AudioHandle);
		AudioHandle->AudioComponent->Stop();

		currentlyPlayingAudio.Remove(AudioHandle);
	}
}

void ASWS_AudioManager::StopAudioByAsset(USoundBase* Base) 
{
	if (currentlyPlayingAudio.Num())
	{
		FAudioHandle* AudioHandle = *currentlyPlayingAudio.FindByPredicate([&](FAudioHandle* AudioHandle)
			{
				return AudioHandle->AudioData.SoundCue == Base;
			});

		StopAudioByHandle(*AudioHandle);
	}
}

void ASWS_AudioManager::RefreshAudioHandlePool(FAudioHandle& handle) 
{
	audioHandlePool.Add(&handle);
	currentlyPlayingAudio.Remove(&handle);
}

FAudioHandle ASWS_AudioManager::PlayAudioByName(const FString& Name, const UObject* WorldContextObject, FVector Location, FRotator Rotation, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundAttenuation* AttenuationSettings, USoundConcurrency* ConcurrencySettings, bool bAutoDestroy)
{
	if (SoundList.Num())
	{
		FAudioData** AudioData = SoundList.FindByPredicate([&](FAudioData* AudioData)
			{
				return AudioData->Name == Name;
			});

		PlayAudioByAudioData(AudioData, WorldContextObject, Location, Rotation, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings, bAutoDestroy);
	}

	return NullHandle;
}

FAudioHandle ASWS_AudioManager::PlayAudioByID(int32 ID, const UObject* WorldContextObject, FVector Location, FRotator Rotation, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundAttenuation* AttenuationSettings, USoundConcurrency* ConcurrencySettings, bool bAutoDestroy) 
{
	if (SoundList.Num())
	{
		FAudioData** AudioData = SoundList.FindByPredicate([&](FAudioData* AudioData)
			{
				return AudioData->AudioID == ID;
			});

		return PlayAudioByAudioData(AudioData, WorldContextObject, Location, Rotation, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings, bAutoDestroy);
	}
	return NullHandle;
}

FAudioHandle& ASWS_AudioManager::PlayAudioByAudioData(FAudioData** FoundEntry, const UObject* WorldContextObject, FVector Location, FRotator Rotation, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundAttenuation* AttenuationSettings, USoundConcurrency* ConcurrencySettings, bool bAutoDestroy)
{
	if (!FoundEntry)
		return ASWS_AudioManager::NullHandle;

	FAudioHandle* NewEntry = new FAudioHandle();
	NewEntry->AudioData = **FoundEntry;

	audioHandlePool.Add(NewEntry);
	NewEntry->AudioComponent = UGameplayStatics::SpawnSoundAtLocation(WorldContextObject, (*FoundEntry)->SoundCue, Location, Rotation, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings, bAutoDestroy);
	
	currentlyPlayingAudio.Add(NewEntry);
	return *NewEntry;
}

FAudioHandle ASWS_AudioManager::PlayAudioByAsset(const UObject* WorldContextObject, USoundBase* Sound, FVector Location, FRotator Rotation, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundAttenuation* AttenuationSettings, USoundConcurrency* ConcurrencySettings, bool bAutoDestroy)
{
	if (SoundList.Num())
	{
		FAudioData** AudioData = SoundList.FindByPredicate([&](FAudioData* AudioData)
			{
				return AudioData->SoundCue == Sound;
			});

		return PlayAudioByAudioData(AudioData, WorldContextObject, Location, Rotation, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings, bAutoDestroy);
	}

	return NullHandle;
}

int32 ASWS_AudioManager::GetSoundID(USoundCue* cue) 
{
	if (currentlyPlayingAudio.Num())
	{
		FAudioData* AudioData = *SoundList.FindByPredicate([&](FAudioData* AudioData)
			{
				return AudioData->SoundCue == cue;
			});

		return AudioData->AudioID;
	}

	return 0;
}

USoundCue* ASWS_AudioManager::GetSoundCueByName(const FString& Name) 
{
	if (SoundList.Num())
	{
		for (int i = 0; i != SoundList.Num(); i++)
		{
			FAudioData* Sound = SoundList[i];
			if (Sound->Name == Name)
				return Sound->SoundCue;
		}
	}

	return nullptr;
}

USoundCue* ASWS_AudioManager::GetSoundByID(int32 ID) 
{
	if (SoundList.Num())
	{
		for (int i = 0; i != SoundList.Num(); i++)
		{
			FAudioData* Sound = SoundList[i];
			if (Sound->AudioID == ID)
				return Sound->SoundCue;
		}
	}

	return nullptr;
}

ASWS_AudioManager* ASWS_AudioManager::GetAudioManager(UObject* WorldContextObject) 
{
	if (!instance)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(GEngine, EGetWorldErrorMode::Assert);
		instance = World->SpawnActor<ASWS_AudioManager>();

		instance->OnAudioManagerSpawned.Broadcast(instance);
		return instance;
	}
	return instance;
}


