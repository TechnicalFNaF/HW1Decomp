#pragma once
#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "SWGVRSettings.generated.h"

UCLASS(Config=EditorUserSettings)
class SWGVR_API USWGVRSettings : public UDeveloperSettings
{
    GENERATED_BODY()

    USWGVRSettings();

public:

    UPROPERTY(Config, EditAnywhere)
    bool bEnableCameraLocator;
    
    UPROPERTY(Config, EditAnywhere)
    bool bForcePickupTesting;
    
    UPROPERTY(Config, EditAnywhere)
    bool bForcePickupDebugDisplay;
    
    UPROPERTY(Config, EditAnywhere)
    bool bForceDS4Enabled;
    
    UPROPERTY(Config, EditAnywhere)
    bool bAllowNonVR;
};