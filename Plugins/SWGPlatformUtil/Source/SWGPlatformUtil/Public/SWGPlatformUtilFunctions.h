#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ESWGEditor.h"
#include "ESWGPlatform.h"
#include "SWGPlatformUtilFunctions.generated.h"

UCLASS(BlueprintType)
class SWGPLATFORMUTIL_API USWGPlatformUtilFunctions : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    USWGPlatformUtilFunctions();

    UFUNCTION(BlueprintCallable)
    static void SwitchOnPlatform(ESWGPlatform& Platform);
    
    UFUNCTION(BlueprintCallable)
    static void IsInEditorSwitch(ESWGEditor& Editor);
    
    UFUNCTION(BlueprintPure)
    static bool IsInEditor();
    
    UFUNCTION(BlueprintPure)
    static FString GetVersionString();
    
    UFUNCTION(BlueprintPure)
    static ESWGPlatform GetBuildPlatform();
    
};

