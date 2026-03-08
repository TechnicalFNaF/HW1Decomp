#pragma once
#include "CoreMinimal.h"
#include "AICharacterBase.h"
#include "Engine/DataTable.h"
#include "UObject/Interface.h"

#include "NPCBaseInterface.generated.h"

UENUM()
enum class AIBaseAxisDirection : uint8 
{
	Horizontal = 0x80,
	Vertical = 0x40,
};
ENUM_CLASS_FLAGS(AIBaseAxisDirection);

UENUM()
enum class AIScareDirection : uint8
{
	Right = 0x81,
	Left = 0x82,
	Up = 0x41,
	Down = 0x42,
};
ENUM_CLASS_FLAGS(AIScareDirection);

UENUM()
enum class AILifeCycle : uint8 
{
	Alive,
	Dead,
};

USTRUCT(BlueprintType)
struct FAIOffsetData : public FTableRowBase 
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AIScareDirection AIDir;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FTransform OffsettransformData;
};

USTRUCT(BlueprintType)
struct FAIDirectionOffsetData : public FTableRowBase 
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AAICharacterBase> AIType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FAIOffsetData> OffsettransformData;
};

USTRUCT(BlueprintType)
struct FAIDatabase : public FTableRowBase 
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FAIDirectionOffsetData> AIScareData;
};

UINTERFACE(Blueprintable, MinimalAPI)
class UNPCBaseInterface : public UInterface 
{
	GENERATED_BODY()
};

class INPCBaseInterface : public IInterface 
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetHealth(float health);
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetAILifeCycle(AILifeCycle lifeCycle);
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	float GetHealth();
};

