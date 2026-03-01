#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ELevelType.h"
#include "GameLevels.generated.h"

class UWorld;

USTRUCT(BlueprintType)
struct FGameLevels : public FTableRowBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int32 TokenRequired;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TSoftObjectPtr<UWorld> Level;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int32 LevelID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TEnumAsByte<ELevelType> LevelType;
    
    FREDDYS_API FGameLevels();
};

