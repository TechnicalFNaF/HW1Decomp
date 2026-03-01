#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AILifeCycle.h"
#include "NPCBaseInterface.generated.h"

UINTERFACE(Blueprintable, MinimalAPI)
class UNPCBaseInterface : public UInterface {
    GENERATED_BODY()
};

class INPCBaseInterface : public IInterface {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void SetHealth(float health);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void SetAILifeCycle(AILifeCycle lifeCycle);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    float GetHealth();
    
};

