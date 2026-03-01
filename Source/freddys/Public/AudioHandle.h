#pragma once
#include "CoreMinimal.h"
#include "AudioData.h"
#include "AudioHandle.generated.h"

class UAudioComponent;

USTRUCT(BlueprintType)
struct FAudioHandle {
    GENERATED_BODY()
public:
    UPROPERTY(VisibleAnywhere)
    FAudioData AudioData;
    
    UPROPERTY(Instanced, VisibleAnywhere)
    UAudioComponent* AudioComponent;
    
    FREDDYS_API FAudioHandle();
};

