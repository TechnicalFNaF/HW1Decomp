#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "AIScareDirection.h"
#include "AIOffsetData.generated.h"

USTRUCT(BlueprintType)
struct FAIOffsetData : public FTableRowBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    AIScareDirection AIDir;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FTransform OffsettransformData;
    
    FREDDYS_API FAIOffsetData();
};

