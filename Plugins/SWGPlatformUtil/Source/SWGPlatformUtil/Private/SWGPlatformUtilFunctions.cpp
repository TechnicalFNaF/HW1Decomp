#include "SWGPlatformUtilFunctions.h"

#include "SWGPlatformSettings.h"

void USWGPlatformUtilFunctions::SwitchOnPlatform(ESWGPlatform& Platform) 
{
	Platform = GetBuildPlatform();
}

void USWGPlatformUtilFunctions::IsInEditorSwitch(ESWGEditor& Editor) 
{
	Editor = IsInEditor() ? ESWGEditor::InEditor : ESWGEditor::NotInEditor;
}

bool USWGPlatformUtilFunctions::IsInEditor() 
{
	return FPlatformProperties::HasEditorOnlyData();
}

FString USWGPlatformUtilFunctions::GetVersionString() 
{
	static FString VersionString = TEXT("unversioned");
	return VersionString;
}

ESWGPlatform USWGPlatformUtilFunctions::GetBuildPlatform() 
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