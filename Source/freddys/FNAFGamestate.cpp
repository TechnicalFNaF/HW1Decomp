#include "FNAFGamestate.h"

// Matching
void AFNAFGamestate::SetVictoryCondition_Implementation(GLVictoryState state) // param name does not match the one in header
{
	VictoryState = state;
}

// Matching
void AFNAFGamestate::SetGameState_Implementation(GLGameState state) // param name does not match the one in header
{
	GameState = state;
}

// Matching
GLVictoryState AFNAFGamestate::GetVictoryCondition_Implementation()
{
	return VictoryState;
}

// Matching
GLGameState AFNAFGamestate::GetGameState_Implementation()
{
	return GameState;
}