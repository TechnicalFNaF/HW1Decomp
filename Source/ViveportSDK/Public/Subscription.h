#pragma once
#include "CoreMinimal.h"
#include "StatusDetail.h"
#include "TimePeriod.h"
#include "Subscription.generated.h"

USTRUCT()
struct FSubscription {
    GENERATED_BODY()
public:
    UPROPERTY()
    FString app_id;
    
    UPROPERTY()
    FString order_id;
    
    UPROPERTY()
    FString subscription_id;
    
    UPROPERTY()
    FString price;
    
    UPROPERTY()
    FString currency;
    
    UPROPERTY()
    int64 subscribed_timestamp;
    
    UPROPERTY()
    FTimePeriod free_trial_period;
    
    UPROPERTY()
    FTimePeriod charge_period;
    
    UPROPERTY()
    int32 number_of_charge_period;
    
    UPROPERTY()
    FString plan_id;
    
    UPROPERTY()
    FString plan_name;
    
    UPROPERTY()
    FString status;
    
    UPROPERTY()
    FStatusDetail status_detail;
    
    VIVEPORTSDK_API FSubscription();
};

