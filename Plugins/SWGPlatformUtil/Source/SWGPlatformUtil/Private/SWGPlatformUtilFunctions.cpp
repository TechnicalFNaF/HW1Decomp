#include "SWGPlatformUtilFunctions.h"

USWGPlatformUtilFunctions::USWGPlatformUtilFunctions() {
}

void USWGPlatformUtilFunctions::SwitchOnPlatform(ESWGPlatform& Platform) {
}

void USWGPlatformUtilFunctions::IsInEditorSwitch(ESWGEditor& Editor) {
}

bool USWGPlatformUtilFunctions::IsInEditor() {
    return false;
}

FString USWGPlatformUtilFunctions::GetVersionString() {
    return TEXT("");
}

ESWGPlatform USWGPlatformUtilFunctions::GetBuildPlatform() {
    return ESWGPlatform::Steam;
}


