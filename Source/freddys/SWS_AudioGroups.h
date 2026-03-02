#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SWS_AudioGroups.generated.h"

UCLASS()
class FREDDYS_API ASWS_AudioGroups : public AActor {
	GENERATED_BODY()
public:
	ASWS_AudioGroups(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced)
	class USWS_GroupComponent* AudioGroupComponent;

	class ASWS_AudioManager* AudioManager;
	int GroupID;

protected:

	virtual void BeginPlay() override;

public: 

	virtual void Tick(float DeltaSeconds);
};

