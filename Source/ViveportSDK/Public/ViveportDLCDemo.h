#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ViveportDLCDemo.generated.h"

UCLASS(ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class VIVEPORTSDK_API UViveportDLCDemo : public UActorComponent {
    GENERATED_BODY()
public:
    UViveportDLCDemo(const FObjectInitializer& ObjectInitializer);

};

