#pragma once
#include "CoreMinimal.h"
#include "IsReadyJsonResponse.generated.h"

USTRUCT()
struct FIsReadyJsonResponse {
    GENERATED_BODY()
public:
    UPROPERTY()
    int32 statusCode;
    
    UPROPERTY()
    FString currencyName;
    
    UPROPERTY()
    FString Message;
    
    VIVEPORTSDK_API FIsReadyJsonResponse();
};

