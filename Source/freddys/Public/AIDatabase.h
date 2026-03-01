#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AIDirectionOffsetData.h"
#include "AIDatabase.generated.h"

USTRUCT(BlueprintType)
struct FAIDatabase : public FTableRowBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAIDirectionOffsetData> AIScareData;
    
    FREDDYS_API FAIDatabase();
};

