#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ViveportUserStatsDemo.generated.h"

UCLASS(ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class VIVEPORTSDK_API UViveportUserStatsDemo : public UActorComponent {
    GENERATED_BODY()
public:
    UViveportUserStatsDemo(const FObjectInitializer& ObjectInitializer);

};

