#pragma once
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SWS_SaveGame.generated.h"

USTRUCT()
struct FSaveFileFormat 
{
	GENERATED_BODY()

	int score;
	int tokensEarnt;
	FString playerName;
};

// Unused to my knowledge
UCLASS()
class FREDDYS_API USWS_SaveGame : public USaveGame 
{
	GENERATED_BODY()

public:
	
	FSaveFileFormat* SaveFile;

	/*
	* Do not exist in executable, probably unused
	*
	* public struct FSaveFileFormat* LoadSaveFile(class FString, int)
	* public void SaveGame(class FString, bool, int)
	* public struct FSaveFileFormat* LoadGame()
	*/
};