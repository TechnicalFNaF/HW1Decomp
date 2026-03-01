#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SWS_AudioGroups.generated.h"

class USWS_GroupComponent;

UCLASS()
class FREDDYS_API ASWS_AudioGroups : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced)
    USWS_GroupComponent* AudioGroupComponent;
    
    ASWS_AudioGroups(const FObjectInitializer& ObjectInitializer);

};

