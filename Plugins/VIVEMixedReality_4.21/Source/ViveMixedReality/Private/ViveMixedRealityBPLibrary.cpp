#include "ViveMixedRealityBPLibrary.h"

UViveMixedRealityBPLibrary::UViveMixedRealityBPLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Log(TEXT("*** ViveMixedRealityBP: Super"));
}

void UViveMixedRealityBPLibrary::AddMixedRealityComponent(AMixedRealityComponent*& pMixedRealityComponent, AActor* pVRPawnTarget, FLinearColor pChromaColor, APlayerCameraManager* pCharacterCamera)
{
}

void UViveMixedRealityBPLibrary::EnableMixedReality(AMixedRealityComponent* pMixedRealityComponent, int32 pCameraTrackerID) 
{
}

void UViveMixedRealityBPLibrary::DisableMixedReality(AMixedRealityComponent* pMixedRealityComponent) 
{
	Log(TEXT("*** ViveMixedRealityBP: DisableMixedReality"));

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