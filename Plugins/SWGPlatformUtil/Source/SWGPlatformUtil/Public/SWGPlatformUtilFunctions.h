#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SWGPlatformUtilFunctions.generated.h"

UCLASS(BlueprintType)
class SWGPLATFORMUTIL_API USWGPlatformUtilFunctions : public UBlueprintFunctionLibrary 
{
    GENERATED_BODY()

public:
    USWGPlatformUtilFunctions();

    UFUNCTION(BlueprintCallable, meta=(ExpandEnumAsExecs="Platform"))
    static void SwitchOnPlatform(ESWGPlatform& Platform);
    
    UFUNCTION(BlueprintCallable, meta = (ExpandEnumAsExecs = "Editor"))
    static void IsInEditorSwitch(ESWGEditor& Editor);
    
    UFUNCTION(BlueprintPure)
    static bool IsInEditor();
    
    UFUNCTION(BlueprintPure)
    static FString GetVersionString();
    
    UFUNCTION(BlueprintPure)
    static ESWGPlatform GetBuildPlatform();
    
};

