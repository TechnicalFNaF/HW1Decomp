#pragma once
#include "CoreUObject.h"
#include "ViveportArcadeSessionType.h"
#include "ViveportArcadeSession.generated.h"

/**
*	APIs of Viveport Arcade Session SDK
*/
UCLASS()
class VIVEPORTSDK_API UViveportArcadeSession : public UObject
{
    GENERATED_BODY()

public:
    static void IsReady(SessionListener *listener);
    static void Start(SessionListener *listener);
    static void Stop(SessionListener *listener);
};