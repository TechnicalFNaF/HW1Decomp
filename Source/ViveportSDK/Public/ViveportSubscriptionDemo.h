#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ViveportSubscriptionDemo.generated.h"

UCLASS(ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class VIVEPORTSDK_API UViveportSubscriptionDemo : public UActorComponent {
    GENERATED_BODY()
public:
    UViveportSubscriptionDemo(const FObjectInitializer& ObjectInitializer);

};

