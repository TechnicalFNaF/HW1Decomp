#pragma once
#include "CoreMinimal.h"
#include "SWGVRTypes.generated.h"

UENUM()
enum class EGrabSnapType : uint8 
{
	LocationToHand,
	SnapToHand,
	None,
};

UENUM()
enum class ESWGVRControllerType : uint8 
{
	SteamVR,
	Oculus,
	PS4Move,
	DUALSHOCK4,
	DUALSHOCK4_VR,
	MouseAndKeyboard,
	Switch,
	XBox,
};

UENUM()
enum class EVRHandType : uint8 
{
	None,
	Left,
	Right,
	Both,
};

UDELEGATE() DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnControllerTrackingChanged);
UDELEGATE() DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnGrabbableEvent, class ASWGVRCharacter*, Sender, class AActor*, DroppedActor, EVRHandType, Hand);