#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ViveportUserDemo.generated.h"

UCLASS(ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class VIVEPORTSDK_API UViveportUserDemo : public UActorComponent {
    GENERATED_BODY()
public:
    UViveportUserDemo(const FObjectInitializer& ObjectInitializer);

};

