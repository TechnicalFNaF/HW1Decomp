#include "LevelDB.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

ULevelDB* ULevelDB::instance = nullptr;

void ULevelDB::LoadLevelByName(const FString& LevelName) 
{
	for (FGameLevels GameLevel : GameLevels)
	{
		if (GameLevel.Level.GetAssetName() == LevelName)
		{
			FString LevelString = GameLevel.Level.GetAssetName();

			UGameplayStatics::OpenLevel(GetWorld(), *LevelString, true);
		}
	}
}

void ULevelDB::LoadLevelByID(int32 LevelID) 
{
	// They are calling a copy ctr, eventually change
	for (FGameLevels GameLevel : GameLevels)
	{
		if (GameLevel.LevelID == LevelID)
		{
			FString LevelString = GameLevel.Level.GetAssetName();

			UGameplayStatics::OpenLevel(GetWorld(), *LevelString, true);
		}
	}
}

void ULevelDB::LoadLevel(TSoftObjectPtr<UWorld> Level) 
{
	// bro... this sucks
	for (FGameLevels GameLevel : GameLevels)
	{
		if (GameLevel.Level == Level)
		{
			FString LevelString = GameLevel.Level.GetAssetName();

			UGameplayStatics::OpenLevel(GetWorld(), *LevelString, true);
		}
	}
}

int32 ULevelDB::GetLevelIDByName(const FString& Name) 
{
	for (FGameLevels GameLevel : GameLevels)
	{
		if (GameLevel.Level.GetAssetName() == Name)
		{
			return GameLevel.LevelID;
		}
	}

	return UINT_MAX;
}

int32 ULevelDB::GetLevelID(TSoftObjectPtr<UWorld> Level) 
{
	for (FGameLevels GameLevel : GameLevels)
	{
		if (GameLevel.Level == Level)
		{
			return GameLevel.LevelID;
		}
	}

	return UINT_MAX;
}

ULevelDB* ULevelDB::CreateLevelDB(UObject* Owner) 
{
	if (!instance)
	{
		instance = NewObject<ULevelDB>(Owner);
	}

	return instance;
}