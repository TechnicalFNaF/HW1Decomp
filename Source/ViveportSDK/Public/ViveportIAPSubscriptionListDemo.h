#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ViveportIAPSubscriptionListDemo.generated.h"

UCLASS(ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class VIVEPORTSDK_API UViveportIAPSubscriptionListDemo : public UActorComponent {
    GENERATED_BODY()
public:
    UViveportIAPSubscriptionListDemo(const FObjectInitializer& ObjectInitializer);

};

