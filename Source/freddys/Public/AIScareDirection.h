#pragma once
#include "CoreMinimal.h"
#include "AIScareDirection.generated.h"

UENUM()
enum class AIScareDirection : uint8 {
    Right = 129,
    Left,
    Up = 65,
    Down,
};

