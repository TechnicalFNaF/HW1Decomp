#pragma once
#include "CoreMinimal.h"
#include "FNAF_Collectables.h"
#include "Engine/DeveloperSettings.h"

#include "FNAFEditorSettings.generated.h"

UCLASS(Config=EditorUserSettings)
class FREDDYS_API UFNAFEditorSettings : public UDeveloperSettings
{
    GENERATED_BODY()
public:
    UPROPERTY(Config, EditAnywhere)
    EFNAFGameType GameType;
    
    UPROPERTY(Config, EditAnywhere)
    bool HasHalloweenDLC;
    
    UFNAFEditorSettings();
};