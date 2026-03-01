#pragma once
#include "CoreMinimal.h"
#include "EGrabSnapType.generated.h"

UENUM()
enum class EGrabSnapType : uint8 {
    LocationToHand,
    SnapToHand,
    None,
};

