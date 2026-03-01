#pragma once
#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "HeldCollisionInfo.generated.h"

USTRUCT(BlueprintType)
struct FHeldCollisionInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite)
    bool bUsePhysics;
    
    UPROPERTY(BlueprintReadWrite)
    TEnumAsByte<ECollisionEnabled::Type> Collision;
    
    SWGVR_API FHeldCollisionInfo();
};

