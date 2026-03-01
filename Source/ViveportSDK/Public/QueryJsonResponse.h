#pragma once
#include "CoreMinimal.h"
#include "QueryJsonResponse.generated.h"

USTRUCT()
struct FQueryJsonResponse {
    GENERATED_BODY()
public:
    UPROPERTY()
    int32 statusCode;
    
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
    
    UPROPERTY()
    FString Message;
    
    VIVEPORTSDK_API FQueryJsonResponse();
};

