// Copyright 2018 Foo Hoang / HTC VIVE. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include <SteamVRFunctionLibrary.h>
#include <Camera/PlayerCameraManager.h>
#include <Engine/SceneCapture2D.h>
#include <Components/SceneCaptureComponent2D.h>
#include "Kismet/KismetRenderingLibrary.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "SteamVRChaperoneComponent.h"
#include "SteamVRFunctionLibrary.h"
#include "MixedRealityComponent.generated.h"

UCLASS()
class AMixedRealityComponent : public AActor
{
	GENERATED_BODY()
	AMixedRealityComponent(const FObjectInitializer & ObjectInitializer);
	~AMixedRealityComponent();

public:
	void init(AActor* target, APlayerCameraManager* character, FLinearColor chromacolor);
	void StartMixedReality(int32 trackerID);
	void StopMixedReality();

private:
	AActor* Target;
	APlayerCameraManager* Character;
	int32 Tracker;
	UWorld* World;
	FLinearColor ChromaColor;
	FVector OffsetLocation;
	FRotator OffsetRotation;
	float FOV;
	float Far;
	FIntPoint screenresolution;
	UMaterial* QuadviewMaterial;
	UTextureRenderTarget2D* RenderTargetFar;
	UTextureRenderTarget2D* RenderTargetNear;
	UMaterialInstanceDynamic* PostProcessFar;
	UMaterialInstanceDynamic* PostProcessNear;
	UTextureRenderTarget2D* RenderTargetQuad;
	UMaterialParameterCollection* PostprocessParams;
	USceneComponent* CaptureComponents;
	ASceneCapture2D* SceneCaptureActorNear;
	ASceneCapture2D* SceneCaptureActorFar;
	USceneCaptureComponent2D* SceneCaptureFar;
	USceneCaptureComponent2D* SceneCaptureNear;

	bool LoadConfig();
	bool SetupCapture();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual bool ShouldTickIfViewportsOnly() const override;

	bool FileLoadString(FString FileNameA, FString& SaveTextA);
	void Log(FString pString);
};