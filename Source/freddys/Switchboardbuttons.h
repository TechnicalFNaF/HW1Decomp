#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/EngineTypes.h"
#include "Switchboardbuttons.generated.h"

class UPrimitiveComponent;

UCLASS()
class FREDDYS_API ASwitchboardbuttons : public AActor 
{
	GENERATED_BODY()

public:

	ASwitchboardbuttons(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintImplementableEvent)
	void OnSwitchBoardButtonPessed(const FString& buttonidentification);
	
protected:

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
protected:

	// TODO: make uproperty as this could become a stale ptr
	class UBoxComponent* boxComponent;

	UPROPERTY(EditAnywhere)
	FString buttonID;

	bool powerOutageHasBeenCompleted;
	bool buttonPressedDelay;
};

