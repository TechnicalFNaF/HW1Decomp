#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HeldGrabbableInfo.h"
#include "MotionControllerInfo.generated.h"

class AActor;
class UPrimitiveComponent;

USTRUCT(BlueprintType)
struct FMotionControllerInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadOnly)
    FVector OldWorldPosition;
    
    UPROPERTY(BlueprintReadOnly)
    FVector Velocity;
    
    UPROPERTY(BlueprintReadOnly)
    FVector InstantaneousVelocity;
    
    UPROPERTY(BlueprintReadOnly)
    TArray<FVector> PreviousPositions;
    
    UPROPERTY(BlueprintReadOnly)
    TArray<AActor*> HoveredObjects;
    
    UPROPERTY(BlueprintReadOnly)
    TArray<AActor*> HoveredGrabbables;
    
    UPROPERTY(BlueprintReadOnly)
    TArray<AActor*> HeldGrabbables;
    
    UPROPERTY(BlueprintReadOnly)
    TMap<AActor*, FHeldGrabbableInfo> HeldInfo;
    
    UPROPERTY(BlueprintReadOnly)
    AActor* ClosestGrabbableActor;
    
    UPROPERTY(BlueprintReadOnly)
    float ClosestGrabbableDistance;
    
    UPROPERTY(BlueprintReadOnly)
    AActor* ClosestHoveredActor;
    
    UPROPERTY(BlueprintReadOnly, Instanced)
    UPrimitiveComponent* ClosestHoveredComponent;
    
    UPROPERTY(BlueprintReadOnly)
    float ClosestDistance;
    
    UPROPERTY(BlueprintReadOnly)
    bool bIsTracked;
    
    SWGVR_API FMotionControllerInfo();
};

