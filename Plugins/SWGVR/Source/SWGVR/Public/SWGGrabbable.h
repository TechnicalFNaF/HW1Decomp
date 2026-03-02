#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SWGVRTypes.h"
#include "SWGGrabbable.generated.h"

class ASWGVRCharacter;

UINTERFACE(Blueprintable, MinimalAPI)
class USWGGrabbable : public UInterface
{
    GENERATED_BODY()
};

class ISWGGrabbable : public IInterface
{
    GENERATED_BODY()
    
public:
    UFUNCTION(BlueprintNativeEvent)
    void OnVRReleased(ASWGVRCharacter* Grabber, EVRHandType Hand, const FVector& ReleaseVelocity);
    
    UFUNCTION(BlueprintNativeEvent)
    void OnVRGrabbed(ASWGVRCharacter* Grabber, EVRHandType Hand);
    
    UFUNCTION(BlueprintNativeEvent)
    bool AttemptRelease(ASWGVRCharacter* Grabber, EVRHandType Hand);
    
    UFUNCTION(BlueprintNativeEvent)
    void AttemptGrab(ASWGVRCharacter* Grabber, EVRHandType Hand, bool& canGrab, EGrabSnapType& SnapType, bool& snapLocation, bool& snapRotation, FVector& AttachmentOffsetLocation, FRotator& AttachmentOffsetRotation);
    
};

