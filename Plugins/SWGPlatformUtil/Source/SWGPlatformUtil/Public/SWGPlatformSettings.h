#pragma once
#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "SWGPlatformSettings.generated.h"

UENUM()
enum class ESWGPlatform : uint8
{
    Steam,
    Oculus,
    PS4,
    Switch,
    XBoxOne,
};

UENUM()
enum class ESWGEditor : uint8 
{
    InEditor,
    NotInEditor,
};

UCLASS(Config=Game)
class SWGPLATFORMUTIL_API USWGPlatformSettings : public UDeveloperSettings 
{
    GENERATED_BODY()

private:
    UPROPERTY(Config, EditAnywhere)
    ESWGPlatform BuildPlatform;
};

