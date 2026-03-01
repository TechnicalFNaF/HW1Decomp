#include "FNAFEditorSettings.h"

UFNAFEditorSettings::UFNAFEditorSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GameType = EFNAFGameType::Normal;
	HasHalloweenDLC = true;
}
