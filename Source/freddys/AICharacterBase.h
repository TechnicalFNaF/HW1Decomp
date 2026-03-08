#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AICharacterBase.generated.h"

UCLASS()
class FREDDYS_API AAICharacterBase : public ACharacter 
{
	GENERATED_BODY()

public:
	AAICharacterBase();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
};