#pragma once
#include "CoreMinimal.h"
#include "GetBalanceJsonResponse.generated.h"

USTRUCT()
struct FGetBalanceJsonResponse {
    GENERATED_BODY()
public:
    UPROPERTY()
    int32 statusCode;
    
    UPROPERTY()
    FString currencyName;
    
    UPROPERTY()
    FString balance;
    
    UPROPERTY()
    FString Message;
    
    VIVEPORTSDK_API FGetBalanceJsonResponse();
};

