#pragma once
#include "CoreMinimal.h"
#include "SessionResult.generated.h"

USTRUCT()
struct FSessionResult {
    GENERATED_BODY()
public:
    UPROPERTY()
    FString pchAppID;
    
    UPROPERTY()
    FString pchGuid;
    
    VIVEPORTSDK_API FSessionResult();
};

