#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ViveportArcadeSessionDemo.generated.h"

UCLASS(ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class VIVEPORTSDK_API UViveportArcadeSessionDemo : public UActorComponent {
    GENERATED_BODY()
public:
    UViveportArcadeSessionDemo(const FObjectInitializer& ObjectInitializer);

};

