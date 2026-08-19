#pragma once

#include "CoreMinimal.h"
#include "SWGPlatformSettings.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SWGPlatformUtilFunctions.generated.h"

UCLASS(BlueprintType)
class SWGPLATFORMUTIL_API USWGPlatformUtilFunctions : public UBlueprintFunctionLibrary 
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta=(ExpandEnumAsExecs="Platform"))
	static void SwitchOnPlatform(ESWGPlatform& Platform)
	{
		Platform = GetBuildPlatform();
	}
	
	UFUNCTION(BlueprintCallable, meta = (ExpandEnumAsExecs = "Editor"))
	static void IsInEditorSwitch(ESWGEditor& Editor)
	{
		Editor = IsInEditor() ? ESWGEditor::InEditor : ESWGEditor::NotInEditor;
	}
	
	UFUNCTION(BlueprintPure)
	static bool IsInEditor()
	{
		return FPlatformProperties::HasEditorOnlyData();
	}
	
	UFUNCTION(BlueprintPure)
	static const FString& GetVersionString();
	
	UFUNCTION(BlueprintPure)
	static ESWGPlatform GetBuildPlatform()
	{
#if PLATFORM_WINDOWS 
		return ESWGPlatform::Steam;
#endif

#if PLATFORM_ANDROID
		return ESWGPlatform::Oculus;
#endif

#if PLATFORM_PS4
		return ESWGPlatform::PS4;
#endif

#if PLATFORM_SWITCH
		return ESWGPlatform::Switch;
#endif

#if PLATFORM_XBOXONE
		return ESWGPlatform::XBoxOne;
#endif
	}
};

