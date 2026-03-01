#pragma once
#include "CoreMinimal.h"
#include "SessionIsReadyJsonResponse.generated.h"

USTRUCT()
struct FSessionIsReadyJsonResponse {
    GENERATED_BODY()
public:
    UPROPERTY()
    int32 statusCode;
    
    UPROPERTY()
    FString appID;
    
    UPROPERTY()
    FString Message;
    
    VIVEPORTSDK_API FSessionIsReadyJsonResponse();
};

