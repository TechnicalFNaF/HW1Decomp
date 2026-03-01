#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AIOffsetData.h"
#include "Templates/SubclassOf.h"
#include "AIDirectionOffsetData.generated.h"

class AAICharacterBase;

USTRUCT(BlueprintType)
struct FAIDirectionOffsetData : public FTableRowBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TSubclassOf<AAICharacterBase> AIType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAIOffsetData> OffsettransformData;
    
    FREDDYS_API FAIDirectionOffsetData();
};

