#pragma once
#include "CoreMinimal.h"
#include "SessionJsonResponse.generated.h"

USTRUCT()
struct FSessionJsonResponse {
    GENERATED_BODY()
public:
    UPROPERTY()
    int32 statusCode;
    
    UPROPERTY()
    FString appID;
    
    UPROPERTY()
    FString Guid;
    
    UPROPERTY()
    FString Message;
    
    VIVEPORTSDK_API FSessionJsonResponse();
};

