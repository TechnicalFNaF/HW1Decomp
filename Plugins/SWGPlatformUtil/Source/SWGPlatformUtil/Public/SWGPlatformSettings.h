#pragma once
#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ESWGPlatform.h"
#include "SWGPlatformSettings.generated.h"

UCLASS(Config=Game)
class SWGPLATFORMUTIL_API USWGPlatformSettings : public UDeveloperSettings {
    GENERATED_BODY()
public:
private:
    UPROPERTY(Config, EditAnywhere)
    ESWGPlatform BuildPlatform;
    
public:
    USWGPlatformSettings();

};

