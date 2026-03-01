#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GLGameState.h"
#include "GLVictoryState.h"
#include "FNAFGamestate.generated.h"

UCLASS()
class FREDDYS_API AFNAFGamestate : public AGameState {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite)
    GLVictoryState VictoryState;
    
    UPROPERTY(BlueprintReadWrite)
    GLGameState GameState;
    
public:
    AFNAFGamestate(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetVictoryCondition(GLVictoryState victory);
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetGameState(GLGameState State);
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    GLVictoryState GetVictoryCondition();
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    GLGameState GetGameState();
    
};

