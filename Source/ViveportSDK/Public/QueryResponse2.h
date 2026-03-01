#pragma once
#include "CoreMinimal.h"
#include "QueryResponse2.generated.h"

USTRUCT(BlueprintType)
struct FQueryResponse2 {
    GENERATED_BODY()
public:
    UPROPERTY()
    FString order_id;
    
    UPROPERTY()
    FString app_id;
    
    UPROPERTY()
    FString purchase_id;
    
    UPROPERTY()
    FString price;
    
    UPROPERTY()
    FString currency;
    
    UPROPERTY()
    int64 paid_timestamp;
    
    UPROPERTY()
    FString user_data;
    
    VIVEPORTSDK_API FQueryResponse2();
};

