#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NPCBaseInterface.h"

#include "AICommonFunctionalities.generated.h"

UCLASS(BlueprintType)
class FREDDYS_API UAICommonFunctionalities : public UBlueprintFunctionLibrary 
{
    GENERATED_BODY()

public:
    UAICommonFunctionalities();

    UFUNCTION(BlueprintCallable)
    static bool isVerticalAxis(AIScareDirection Direction);
    
    UFUNCTION(BlueprintCallable)
    static bool isValidAxisDirection(AIBaseAxisDirection Axis, AIScareDirection Direction);
    
    UFUNCTION(BlueprintCallable)
    static bool isHorizontalAxis(AIScareDirection Direction);
};

