#include "ViveMixedRealityBPLibrary.h"

#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstanceDynamic.h"

UViveMixedRealityBPLibrary::UViveMixedRealityBPLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Log("*** ViveMixedRealityBP: Super");
}

void UViveMixedRealityBPLibrary::AddMixedRealityComponent(AMixedRealityComponent*& pMixedRealityComponent, AActor* pVRPawnTarget, FLinearColor pChromaColor, APlayerCameraManager* pCharacterCamera)
{
	Log("*** ViveMixedRealityBP: Init");

	UWorld* TargetWorld = pVRPawnTarget->GetWorld();

	APlayerCameraManager* CharacterCamera = pCharacterCamera;
	if (!CharacterCamera)
		CharacterCamera = UGameplayStatics::GetPlayerCameraManager(TargetWorld, 0);

	AMixedRealityComponent* SpawnedComp = TargetWorld->SpawnActor<AMixedRealityComponent>();
	SpawnedComp->Target = pVRPawnTarget;
	SpawnedComp->Character = pCharacterCamera;
	SpawnedComp->World = pVRPawnTarget->GetWorld();
	SpawnedComp->screenresolution = UGameUserSettings::GetGameUserSettings()->GetDesktopResolution();

	SpawnedComp->PostProcessNear->SetVectorParameterValue("ChromaColor", pChromaColor);
	SpawnedComp->FinishSpawning(FTransform::Identity);

	SpawnedComp->AttachToActor(pVRPawnTarget, FAttachmentTransformRules::KeepRelativeTransform);
	pMixedRealityComponent = SpawnedComp;
}

void UViveMixedRealityBPLibrary::EnableMixedReality(AMixedRealityComponent* pMixedRealityComponent, int32 pCameraTrackerID) 
{
}

void UViveMixedRealityBPLibrary::DisableMixedReality(AMixedRealityComponent* pMixedRealityComponent) 
{
	Log("*** ViveMixedRealityBP: DisableMixedReality");

	if (pMixedRealityComponent)
		pMixedRealityComponent->StopMixedReality();
}

void UViveMixedRealityBPLibrary::StartMixedReality()
{
}

void UViveMixedRealityBPLibrary::Log(FString pString)
{
	UE_LOG(LogTemp, Display, TEXT("%s"), *pString);
}