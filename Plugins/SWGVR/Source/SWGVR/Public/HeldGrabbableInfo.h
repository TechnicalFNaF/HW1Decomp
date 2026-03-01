#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "Engine/EngineTypes.h"
#include "EGrabSnapType.h"
#include "HeldCollisionInfo.h"
#include "HeldGrabbableInfo.generated.h"

class UPrimitiveComponent;

USTRUCT(BlueprintType)
struct FHeldGrabbableInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite)
    bool bUsePhysics;
    
    UPROPERTY(BlueprintReadWrite)
    TEnumAsByte<ECollisionEnabled::Type> Collision;
    
    UPROPERTY(BlueprintReadOnly)
    TMap<UPrimitiveComponent*, FHeldCollisionInfo> PrimitiveCollisionInfo;
    
    UPROPERTY(BlueprintReadOnly)
    EGrabSnapType GrabSnapType;
    
    UPROPERTY(BlueprintReadWrite)
    FVector AttachmentRelativeLocation;
    
    UPROPERTY(BlueprintReadWrite)
    FRotator AttachmentRelativeRotation;
    
    UPROPERTY(BlueprintReadWrite)
    bool IsLerpingToHand;
    
    SWGVR_API FHeldGrabbableInfo();
};

