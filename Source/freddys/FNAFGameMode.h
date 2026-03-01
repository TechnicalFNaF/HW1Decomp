#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "FNAFGameMode.generated.h"

class ULevelDB;

UCLASS(NonTransient)
class FREDDYS_API AFNAFGameMode : public AGameMode
{
    GENERATED_BODY()
    
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TSubclassOf<ULevelDB> LevelDBClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ULevelDB* LevelDBInstance;
    
    UFUNCTION(BlueprintCallable)
    void SpawnLevelDB();
    
    UFUNCTION(BlueprintImplementableEvent)
    void OnSetLevelDB();
};

