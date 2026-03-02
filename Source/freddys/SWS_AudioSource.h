#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SWS_AudioSource.generated.h"

UCLASS()
class FREDDYS_API ASWS_AudioSource : public AActor 
{
	GENERATED_BODY()

	ASWS_AudioSource(const FObjectInitializer& ObjectInitializer);

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class USoundCue* SoundCueFile;

	int AudioGroupID;
	int AudioSourceGlobalID;
	struct FAudioHandle* AudioHandle;

	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
	void StopAudio(UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
	void PlayAudio(const UObject* WorldContextObject, class USoundBase* Sound, FVector Location, FRotator Rotation, float VolumeMultiplier, float PitchMultiplier, float StartTime, class USoundAttenuation* AttenuationSettings, class USoundConcurrency* ConcurrencySettings, bool bAutoDestroy);
	
	UFUNCTION()
	void DestroyHandle();
};