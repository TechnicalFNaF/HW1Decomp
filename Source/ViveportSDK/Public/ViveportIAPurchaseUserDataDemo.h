#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ViveportIAPurchaseUserDataDemo.generated.h"

UCLASS(ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class VIVEPORTSDK_API UViveportIAPurchaseUserDataDemo : public UActorComponent {
    GENERATED_BODY()
public:
    UViveportIAPurchaseUserDataDemo(const FObjectInitializer& ObjectInitializer);

};

