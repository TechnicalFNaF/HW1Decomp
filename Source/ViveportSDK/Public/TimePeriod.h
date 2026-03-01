#pragma once
#include "CoreMinimal.h"
#include "TimePeriod.generated.h"

USTRUCT(BlueprintType)
struct FTimePeriod {
    GENERATED_BODY()
public:
    UPROPERTY()
    FString time_type;
    
    UPROPERTY()
    int32 Value;
    
    VIVEPORTSDK_API FTimePeriod();
};

