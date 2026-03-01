#pragma once
#include "CoreMinimal.h"
#include "Subscription.h"
#include "QuerySubscriptionJsonResponse.generated.h"

USTRUCT()
struct FQuerySubscriptionJsonResponse {
    GENERATED_BODY()
public:
    UPROPERTY()
    int32 statusCode;
    
    UPROPERTY()
    FString Message;
    
    UPROPERTY()
    TArray<FSubscription> subscriptions;
    
    VIVEPORTSDK_API FQuerySubscriptionJsonResponse();
};

