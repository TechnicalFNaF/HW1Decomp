#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameLevels.h"
#include "LevelDB.generated.h"

class ULevelDB;
class UWorld;

UCLASS(BlueprintType)
class FREDDYS_API ULevelDB : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FGameLevels> GameLevels;
    
    ULevelDB();

    UFUNCTION(BlueprintCallable)
    void LoadLevelByName(const FString& LevelName);
    
    UFUNCTION(BlueprintCallable)
    void LoadLevelByID(int32 LevelID);
    
    UFUNCTION(BlueprintCallable)
    void LoadLevel(TSoftObjectPtr<UWorld> Level);
    
    UFUNCTION(BlueprintCallable)
    int32 GetLevelIDByName(const FString& Name);
    
    UFUNCTION(BlueprintCallable)
    int32 GetLevelID(TSoftObjectPtr<UWorld> Level);
    
    UFUNCTION(BlueprintCallable)
    static ULevelDB* CreateLevelDB(UObject* Owner);
    
};

