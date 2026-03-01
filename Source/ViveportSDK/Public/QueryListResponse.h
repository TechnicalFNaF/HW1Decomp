#pragma once
#include "CoreMinimal.h"
#include "QueryResponse2.h"
#include "QueryListResponse.generated.h"

USTRUCT()
struct FQueryListResponse {
    GENERATED_BODY()
public:
    UPROPERTY()
    int64 total;
    
    UPROPERTY()
    int64 from;
    
    UPROPERTY()
    int64 to;
    
    UPROPERTY()
    TArray<FQueryResponse2> purchaseList;
    
    VIVEPORTSDK_API FQueryListResponse();
};

