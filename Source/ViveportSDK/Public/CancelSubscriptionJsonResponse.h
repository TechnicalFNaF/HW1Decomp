#pragma once
#include "CoreMinimal.h"
#include "CancelSubscriptionJsonResponse.generated.h"

USTRUCT()
struct FCancelSubscriptionJsonResponse {
    GENERATED_BODY()
public:
    UPROPERTY()
    int32 statusCode;
    
    UPROPERTY()
    FString Message;
    
    VIVEPORTSDK_API FCancelSubscriptionJsonResponse();
};

