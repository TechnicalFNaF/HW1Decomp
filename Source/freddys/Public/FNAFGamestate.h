#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "FNAFGamestate.generated.h"

UENUM()
enum class GLVictoryState : uint8 
{
    InProgress,
    Victory,
    Defeat,
};

UENUM()
enum class GLGameState : uint8
{
    PreInit,
    Init,
    Progress,
    Completed,
};

UCLASS()
class FREDDYS_API AFNAFGamestate : public AGameState 
{
    GENERATED_BODY()

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

