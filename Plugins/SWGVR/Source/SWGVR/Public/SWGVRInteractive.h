#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EVRHandType.h"
#include "SWGVRInteractive.generated.h"

class ASWGVRCharacter;

UINTERFACE(Blueprintable, MinimalAPI)
class USWGVRInteractive : public UInterface {
    GENERATED_BODY()
};

class ISWGVRInteractive : public IInterface {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintNativeEvent)
    void OnVRInteract(ASWGVRCharacter* VRCharacter, EVRHandType Hand);
    
};

