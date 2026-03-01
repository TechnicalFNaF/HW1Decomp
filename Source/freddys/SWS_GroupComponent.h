#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SWS_GroupComponent.generated.h"

class ASWS_AudioSource;

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class FREDDYS_API USWS_GroupComponent : public UActorComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<ASWS_AudioSource*> ListOfAudioSources;
    
    USWS_GroupComponent(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void UnRegisterAudioSource(ASWS_AudioSource* cue);
    
    UFUNCTION(BlueprintCallable)
    void RegisterAudioSource(ASWS_AudioSource* cue);
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnVolumeModified(float Volume);
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnPitchModified(float Pitch);
    
    UFUNCTION(BlueprintCallable)
    void ModifyGroupVolumeMultiplier(float Volume);
    
    UFUNCTION(BlueprintCallable)
    void ModifyGroupPitchMultiplier(float Pitch);
    
    UFUNCTION(BlueprintCallable)
    int32 GetTotalFrequency();
    
    UFUNCTION(BlueprintCallable)
    int32 GetTotalAmplitude();
    
};

