#pragma once
#include "CoreMinimal.h"
#include "EVRHandType.h"
#include "OnGrabbableEventDelegate.generated.h"

class AActor;
class ASWGVRCharacter;

UDELEGATE() DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnGrabbableEvent, ASWGVRCharacter*, Sender, AActor*, DroppedActor, EVRHandType, Hand);

