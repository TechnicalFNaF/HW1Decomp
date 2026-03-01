#pragma once
#include "CoreMinimal.h"
#include "RequestSubscriptionJsonResponse.generated.h"

USTRUCT()
struct FRequestSubscriptionJsonResponse {
    GENERATED_BODY()
public:
    UPROPERTY()
    int32 statusCode;
    
    UPROPERTY()
    FString subscription_id;
    
    UPROPERTY()
    FString Message;
    
    VIVEPORTSDK_API FRequestSubscriptionJsonResponse();
};

