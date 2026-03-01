#pragma once
#include "CoreMinimal.h"
#include "GLGameState.generated.h"

UENUM()
enum class GLGameState : uint8 {
    PreInit,
    Init,
    Progress,
    Completed,
};

