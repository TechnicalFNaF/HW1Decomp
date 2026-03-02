#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FNAF_Collectables.generated.h"

UENUM()
enum class EFNAFGameType : uint8
{
	Demo,
	Normal,
	Arcade
};

UCLASS()
class FREDDYS_API AFNAF_Collectables : public AActor 
{
	GENERATED_BODY()
};

