#pragma once
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SWS_SaveGame.generated.h"

USTRUCT()
struct FSaveFileFormat 
{
    GENERATED_BODY()
};

UCLASS()
class FREDDYS_API USWS_SaveGame : public USaveGame 
{
    GENERATED_BODY()

public:

    USWS_SaveGame();
};

