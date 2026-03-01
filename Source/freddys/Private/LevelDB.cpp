#include "LevelDB.h"

ULevelDB::ULevelDB() {
}

void ULevelDB::LoadLevelByName(const FString& LevelName) {
}

void ULevelDB::LoadLevelByID(int32 LevelID) {
}

void ULevelDB::LoadLevel(TSoftObjectPtr<UWorld> Level) {
}

int32 ULevelDB::GetLevelIDByName(const FString& Name) {
    return 0;
}

int32 ULevelDB::GetLevelID(TSoftObjectPtr<UWorld> Level) {
    return 0;
}

ULevelDB* ULevelDB::CreateLevelDB(UObject* Owner) {
    return NULL;
}


