#include "FNAFGamestate.h"

AFNAFGamestate::AFNAFGamestate(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->VictoryState = GLVictoryState::InProgress;
    this->GameState = GLGameState::PreInit;
}

void AFNAFGamestate::SetVictoryCondition_Implementation(GLVictoryState victory) {
}

void AFNAFGamestate::SetGameState_Implementation(GLGameState State) {
}

GLVictoryState AFNAFGamestate::GetVictoryCondition_Implementation() {
    return GLVictoryState::InProgress;
}

GLGameState AFNAFGamestate::GetGameState_Implementation() {
    return GLGameState::PreInit;
}


