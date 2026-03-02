#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SWGVRTypes.h"
#include "SWGVRHoverReceiver.generated.h"

UINTERFACE(Blueprintable, MinimalAPI)
class USWGVRHoverReceiver : public UInterface 
{
	GENERATED_BODY()
};

class ISWGVRHoverReceiver : public IInterface 
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnVRHoverEnd(class ASWGVRCharacter* Sender, EVRHandType Hand);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnVRHoverComponentEnd(class ASWGVRCharacter* Sender, class UPrimitiveComponent* HoveredComponent, EVRHandType Hand);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnVRHoverComponentBegin(class ASWGVRCharacter* Sender, class UPrimitiveComponent* HoveredComponent, EVRHandType Hand);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnVRHoverBegin(class ASWGVRCharacter* Sender, EVRHandType Hand);
};