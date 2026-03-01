#pragma once
#include "CoreMinimal.h"
#include "RequestJsonResponse.generated.h"

USTRUCT()
struct FRequestJsonResponse {
    GENERATED_BODY()
public:
    UPROPERTY()
    int32 statusCode;
    
    UPROPERTY()
    FString purchase_id;
    
    UPROPERTY()
    FString Message;
    
    VIVEPORTSDK_API FRequestJsonResponse();
};

