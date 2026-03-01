#pragma once
#include "CoreMinimal.h"
#include "GLVictoryState.generated.h"

UENUM()
enum class GLVictoryState : uint8 {
    InProgress,
    Victory,
    Defeat,
};

