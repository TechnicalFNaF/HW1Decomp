#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SWGVRTypes.h"
#include "SWGVRHoverReceiver.generated.h"

class ASWGVRCharacter;
class UPrimitiveComponent;

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
    void OnVRHoverEnd(ASWGVRCharacter* Sender, EVRHandType Hand);
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnVRHoverComponentEnd(ASWGVRCharacter* Sender, UPrimitiveComponent* HoveredComponent, EVRHandType Hand);
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnVRHoverComponentBegin(ASWGVRCharacter* Sender, UPrimitiveComponent* HoveredComponent, EVRHandType Hand);
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnVRHoverBegin(ASWGVRCharacter* Sender, EVRHandType Hand);
    
};

