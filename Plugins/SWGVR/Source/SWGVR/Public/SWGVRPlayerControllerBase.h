#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SWGVRPlayerControllerBase.generated.h"

UCLASS()
class SWGVR_API ASWGVRPlayerControllerBase : public APlayerController {
    GENERATED_BODY()
public:
    ASWGVRPlayerControllerBase(const FObjectInitializer& ObjectInitializer);

protected:
    UFUNCTION(BlueprintNativeEvent)
    void OnUsingGamepadChanged();
    
public:
    UFUNCTION(BlueprintPure)
    bool IsUsingGamepad() const;
    
};

