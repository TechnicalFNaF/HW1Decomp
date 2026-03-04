#include "LevelDB.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

ULevelDB* ULevelDB::instance = nullptr;

// Matching
void ULevelDB::LoadLevelByName(FString LevelName) 
{
	for (FGameLevels GameLevel : GameLevels)
	{
		if (GameLevel.Level.GetAssetName() == LevelName)
		{
			UGameplayStatics::OpenLevel(GetWorld(), *GameLevel.Level.GetAssetName(), true);
		}
	}
}

// Matching
void ULevelDB::LoadLevelByID(int32 LevelID) 
{
	// They are calling a copy ctr, eventually change
	for (FGameLevels GameLevel : GameLevels)
	{
		if (GameLevel.LevelID == LevelID)
		{
			UGameplayStatics::OpenLevel(GetWorld(), *GameLevel.Level.GetAssetName(), true);
		}
	}
}

// Matching
void ULevelDB::LoadLevel(TSoftObjectPtr<UWorld> Level) 
{
	bool bLevelInDB = false;
	for (FGameLevels GameLevel : GameLevels)
	{
		if (GameLevel.Level == Level)
		{
			bLevelInDB = true;
		}
	}

	if (bLevelInDB)
	{
		UGameplayStatics::OpenLevel(GetWorld(), *Level.GetAssetName(), true);
	}
}

// Matching
int32 ULevelDB::GetLevelIDByName(FString Name) 
{
	for (FGameLevels GameLevel : GameLevels)
	{
		if (GameLevel.Level.GetAssetName() == Name)
		{
			return GameLevel.LevelID;
		}
	}
	return -1;
}

// Matching
int32 ULevelDB::GetLevelID(TSoftObjectPtr<UWorld> Level) 
{
	for (FGameLevels GameLevel : GameLevels)
	{
		if (GameLevel.Level == Level)
		{
			return GameLevel.LevelID;
		}
	}
	return -1;
}

// Matching
ULevelDB* ULevelDB::CreateLevelDB(UObject* Owner) 
{
	if (!instance)	
	{
		instance = NewObject<ULevelDB>(Owner);
	}
	return instance;
}