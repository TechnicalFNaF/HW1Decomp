#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Sound/SoundCue.h"
#include "SWS_AudioStatics.generated.h"

UENUM()
enum class ERegisterAudio 
{
	REGISTER,
	UNREGISTER,
};

UENUM()
enum class EAudioCategory 
{
	UI,
	FX,
	DEATH,
};

USTRUCT(BlueprintType)
struct FAudioData : public FTableRowBase 
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	uint8 NoiseValue;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	uint8 AudioID;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USoundCue* SoundCue;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USoundClass* SoundCategory;
};


USTRUCT(BlueprintType)
struct FAudioHandle 
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	FAudioData AudioData;

	UPROPERTY(Instanced, VisibleAnywhere)
	UAudioComponent* AudioComponent;
};

UCLASS()
class FREDDYS_API USWS_AudioStatics : public UBlueprintFunctionLibrary 
{
	GENERATED_BODY()
};