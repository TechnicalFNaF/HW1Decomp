#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EVRPlayType.h"
#include "SWGVRUtil.generated.h"

UCLASS(BlueprintType)
class SWGVR_API USWGVRUtil : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    USWGVRUtil();

    UFUNCTION(BlueprintCallable)
    static void SwitchOnPlayType(EVRPlayType& VRPlayMode);
    
    UFUNCTION(BlueprintPure)
    static EVRPlayType GetPlayType();
    
    UFUNCTION(BlueprintCallable)
    static void ChangePlayType(EVRPlayType VRPlayMode);
    
};

