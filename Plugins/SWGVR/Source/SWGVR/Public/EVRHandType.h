#pragma once
#include "CoreMinimal.h"
#include "EVRHandType.generated.h"

UENUM()
enum class EVRHandType : uint8 {
    None,
    Left,
    Right,
    Both,
};

