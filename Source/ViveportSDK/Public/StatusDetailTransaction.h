#pragma once
#include "CoreMinimal.h"
#include "StatusDetailTransaction.generated.h"

USTRUCT(BlueprintType)
struct FStatusDetailTransaction {
    GENERATED_BODY()
public:
    UPROPERTY()
    int64 create_time;
    
    UPROPERTY()
    FString payment_method;
    
    UPROPERTY()
    FString status;
    
    VIVEPORTSDK_API FStatusDetailTransaction();
};

