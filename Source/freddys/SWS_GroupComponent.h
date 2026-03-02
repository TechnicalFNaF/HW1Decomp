#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SWS_GroupComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class FREDDYS_API USWS_GroupComponent : public UActorComponent 
{
	GENERATED_BODY()

public:

	USWS_GroupComponent(const FObjectInitializer& ObjectInitializer);

protected:
	
	virtual void BeginPlay() override;

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<class ASWS_AudioSource*> ListOfAudioSources;

	int GroupID;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Initialize(int id);

	UFUNCTION(BlueprintCallable)
	void UnRegisterAudioSource(class ASWS_AudioSource* cue);
	
	UFUNCTION(BlueprintCallable)
	void RegisterAudioSource(class ASWS_AudioSource* cue);
	
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