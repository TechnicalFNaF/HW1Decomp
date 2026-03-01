#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ViveportIAPSubscriptionDemo.generated.h"

UCLASS(ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class VIVEPORTSDK_API UViveportIAPSubscriptionDemo : public UActorComponent {
    GENERATED_BODY()
public:
    UViveportIAPSubscriptionDemo(const FObjectInitializer& ObjectInitializer);

};

