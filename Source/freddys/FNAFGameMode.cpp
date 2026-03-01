#include "FNAFGameMode.h"
#include "LevelDB.h"

// unsure
void AFNAFGameMode::SpawnLevelDB()
{
	LevelDBInstance = NewObject<ULevelDB>(this, LevelDBClass.Get());
	OnSetLevelDB();
}
