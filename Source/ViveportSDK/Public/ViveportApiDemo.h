#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ViveportApiDemo.generated.h"

UCLASS(ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class VIVEPORTSDK_API UViveportApiDemo : public UActorComponent {
    GENERATED_BODY()
public:
    UViveportApiDemo(const FObjectInitializer& ObjectInitializer);

};

