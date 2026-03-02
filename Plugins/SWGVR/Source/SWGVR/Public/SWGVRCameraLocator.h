#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "SWGVRCameraLocator.generated.h"

UCLASS()
class SWGVR_API ASWGVRCameraLocator : public AActor
{
	GENERATED_BODY()
	
	USceneComponent* Root;
	UArrowComponent* ForwardArrow;
	UArrowComponent* RightArrow;
	
public:
	ASWGVRCameraLocator();

	virtual void BeginPlay() override;
};

