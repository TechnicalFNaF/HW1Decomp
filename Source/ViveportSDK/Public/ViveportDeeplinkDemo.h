#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ViveportDeeplinkDemo.generated.h"

UCLASS(ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class VIVEPORTSDK_API UViveportDeeplinkDemo : public UActorComponent {
    GENERATED_BODY()
public:
    UViveportDeeplinkDemo(const FObjectInitializer& ObjectInitializer);

};

