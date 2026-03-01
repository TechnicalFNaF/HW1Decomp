#include "FNAFGamestate.h"

void AFNAFGamestate::SetVictoryCondition_Implementation(GLVictoryState state) // param name does not match the one in header
{
    VictoryState = state;
}

void AFNAFGamestate::SetGameState_Implementation(GLGameState state) // param name does not match the one in header
{
    GameState = state;
}

GLVictoryState AFNAFGamestate::GetVictoryCondition_Implementation()
{
    return VictoryState;
}

GLGameState AFNAFGamestate::GetGameState_Implementation()
{
    return GameState;
}
