#pragma once
#include "CoreMinimal.h"
#include "ESWGVRControllerType.generated.h"

UENUM()
enum class ESWGVRControllerType : uint8 {
    SteamVR,
    Oculus,
    PS4Move,
    DUALSHOCK4,
    DUALSHOCK4_VR,
    MouseAndKeyboard,
    Switch,
    XBox,
};

