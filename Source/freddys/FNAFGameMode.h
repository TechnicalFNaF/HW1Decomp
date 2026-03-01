#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "FNAFGameMode.generated.h"

UCLASS(NonTransient)
class FREDDYS_API AFNAFGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class ULevelDB> LevelDBClass;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class ULevelDB* LevelDBInstance;
	
	UFUNCTION(BlueprintCallable)
	void SpawnLevelDB();
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnSetLevelDB();
};

