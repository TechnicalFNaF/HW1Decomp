#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AudioData.generated.h"

class USoundClass;
class USoundCue;

USTRUCT(BlueprintType)
struct FAudioData : public FTableRowBase {
    GENERATED_BODY()
public:
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
    
    FREDDYS_API FAudioData();
};

