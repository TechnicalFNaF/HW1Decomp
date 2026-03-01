#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ViveMixedRealityBPLibrary.generated.h"

class AActor;
class AMixedRealityComponent;
class APlayerCameraManager;

UCLASS(BlueprintType)
class UViveMixedRealityBPLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    UViveMixedRealityBPLibrary();

    UFUNCTION(BlueprintCallable)
    static void EnableMixedReality(AMixedRealityComponent* pMixedRealityComponent, int32 pCameraTrackerID);
    
    UFUNCTION(BlueprintCallable)
    static void DisableMixedReality(AMixedRealityComponent* pMixedRealityComponent);
    
    UFUNCTION(BlueprintCallable)
    static void AddMixedRealityComponent(AMixedRealityComponent*& pMixedRealityComponent, AActor* pVRPawnTarget, FLinearColor pChromaColor, APlayerCameraManager* pCharacterCamera);
    
};

