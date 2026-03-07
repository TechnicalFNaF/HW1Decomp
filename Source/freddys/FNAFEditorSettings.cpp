#include "FNAFEditorSettings.h"

// Matching
UFNAFEditorSettings::UFNAFEditorSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GameType = EFNAFGameType::Normal;
	HasHalloweenDLC = true;
}
