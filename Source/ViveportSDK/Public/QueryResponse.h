#pragma once
#include "CoreMinimal.h"
#include "QueryResponse.generated.h"

USTRUCT()
struct FQueryResponse {
    GENERATED_BODY()
public:
    UPROPERTY()
    FString purchase_id;
    
    UPROPERTY()
    FString order_id;
    
    UPROPERTY()
    FString status;
    
    UPROPERTY()
    FString price;
    
    UPROPERTY()
    FString currency;
    
    UPROPERTY()
    int64 paid_timestamp;
    
    VIVEPORTSDK_API FQueryResponse();
};

