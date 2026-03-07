#include "FNAFGameMode.h"
#include "LevelDB.h"

// Matching
void AFNAFGameMode::SpawnLevelDB()
{
	LevelDBInstance = NewObject<ULevelDB>(this, LevelDBClass.Get());
	OnSetLevelDB();
}
