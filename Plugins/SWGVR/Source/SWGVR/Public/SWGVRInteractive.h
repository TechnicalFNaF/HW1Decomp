#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SWGVRTypes.h"
#include "SWGVRInteractive.generated.h"

UINTERFACE(Blueprintable, MinimalAPI)
class USWGVRInteractive : public UInterface 
{
	GENERATED_BODY()
};

class ISWGVRInteractive : public IInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
	void OnVRInteract(class ASWGVRCharacter* VRCharacter, EVRHandType Hand);
};