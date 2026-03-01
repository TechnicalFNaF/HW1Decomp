#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ViveportTokenDemo.generated.h"

UCLASS(ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class VIVEPORTSDK_API UViveportTokenDemo : public UActorComponent {
    GENERATED_BODY()
public:
    UViveportTokenDemo(const FObjectInitializer& ObjectInitializer);

};

