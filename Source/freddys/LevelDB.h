#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Engine/DataTable.h"
#include "LevelDB.generated.h"

UENUM()
enum ELevelType 
{
	Playable,
	Visual
};

USTRUCT(BlueprintType)
struct FGameLevels : public FTableRowBase 
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 TokenRequired;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSoftObjectPtr<UWorld> Level;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 LevelID;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<ELevelType> LevelType;
};

UCLASS(BlueprintType)
class FREDDYS_API ULevelDB : public UObject 
{
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

