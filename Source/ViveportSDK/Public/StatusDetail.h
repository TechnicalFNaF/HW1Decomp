#pragma once
#include "CoreMinimal.h"
#include "StatusDetailTransaction.h"
#include "StatusDetail.generated.h"

USTRUCT(BlueprintType)
struct FStatusDetail {
    GENERATED_BODY()
public:
    UPROPERTY()
    int64 date_next_charge;
    
    UPROPERTY()
    TArray<FStatusDetailTransaction> transactions;
    
    UPROPERTY()
    FString cancel_reason;
    
    VIVEPORTSDK_API FStatusDetail();
};

