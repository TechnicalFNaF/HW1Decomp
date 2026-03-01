#pragma once
#include "CoreMinimal.h"
#include "PurchaseJsonResponse.generated.h"

USTRUCT()
struct FPurchaseJsonResponse {
    GENERATED_BODY()
public:
    UPROPERTY()
    int32 statusCode;
    
    UPROPERTY()
    FString purchase_id;
    
    UPROPERTY()
    int64 paid_timestamp;
    
    UPROPERTY()
    FString Message;
    
    VIVEPORTSDK_API FPurchaseJsonResponse();
};

