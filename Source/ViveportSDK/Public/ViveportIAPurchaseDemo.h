#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ViveportIAPurchaseDemo.generated.h"

UCLASS(ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class VIVEPORTSDK_API UViveportIAPurchaseDemo : public UActorComponent {
    GENERATED_BODY()
public:
    UViveportIAPurchaseDemo(const FObjectInitializer& ObjectInitializer);

};

