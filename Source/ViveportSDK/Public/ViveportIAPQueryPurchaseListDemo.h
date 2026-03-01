#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ViveportIAPQueryPurchaseListDemo.generated.h"

UCLASS(ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class VIVEPORTSDK_API UViveportIAPQueryPurchaseListDemo : public UActorComponent {
    GENERATED_BODY()
public:
    UViveportIAPQueryPurchaseListDemo(const FObjectInitializer& ObjectInitializer);

};

