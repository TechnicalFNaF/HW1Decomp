#pragma once
#include "CoreMinimal.h"
#include "SubscribeJsonResponse.generated.h"

USTRUCT()
struct FSubscribeJsonResponse {
    GENERATED_BODY()
public:
    UPROPERTY()
    int32 statusCode;
    
    UPROPERTY()
    FString subscription_id;
    
    UPROPERTY()
    int64 subscribed_timestamp;
    
    UPROPERTY()
    FString plan_id;
    
    UPROPERTY()
    FString Message;
    
    VIVEPORTSDK_API FSubscribeJsonResponse();
};

