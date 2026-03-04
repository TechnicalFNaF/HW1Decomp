// Copyright 2018 Foo Hoang / HTC VIVE. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "MixedRealityComponent.h"
#include "ViveMixedRealityBPLibrary.generated.h"

UCLASS()
class UViveMixedRealityBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Mixed Reality Component", Keywords = "add mixed reality component mr", DefaultToSelf = Target, AdvancedDisplay = "2"), Category = "Mixed Reality")
		static void AddMixedRealityComponent(
			UPARAM(DisplayName = "Mixed Reality Component") AMixedRealityComponent* &pMixedRealityComponent,
			UPARAM(DisplayName = "VR Pawn Target") AActor* pVRPawnTarget,
			UPARAM(DisplayName = "Chroma Color")FLinearColor pChromaColor,
			UPARAM(DisplayName = "Character Camera")APlayerCameraManager* pCharacterCamera);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Enable Mixed Reality", Keywords = "enable mixed reality mr", DefaultToSelf = Target, AdvancedDisplay = "1"), Category = "Mixed Reality")
		static void EnableMixedReality(
			UPARAM(DisplayName = "Mixed Reality Component") AMixedRealityComponent* pMixedRealityComponent,
			UPARAM(DisplayName = "Camera Tracker") int32 pCameraTrackerID);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Disable Mixed Reality", Keywords = "disable mixed reality mr", DefaultToSelf = Target), Category = "Mixed Reality")
		static void DisableMixedReality(
			UPARAM(DisplayName = "Mixed Reality Component") AMixedRealityComponent* pMixedRealityComponent);
		void StartMixedReality();

private:
	static void Log(FString pString);
};
