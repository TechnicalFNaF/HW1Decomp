#pragma once

#include "CoreUObject.h"
#include "ViveportArcadeSessionType.h"
#include "ViveportArcadeSessionTypeInternal.generated.h"

/**
*	Json response of 'IsReady' API.
*/
USTRUCT()
struct FSessionIsReadyJsonResponse
{
    GENERATED_BODY()

    UPROPERTY()
    int32 statusCode;

    UPROPERTY()
    FString appID;

    UPROPERTY()
    FString message;
};

/**
*	Json response of 'Start' 'Stop' API.
*/
USTRUCT()
struct FSessionJsonResponse
{
    GENERATED_BODY()

    UPROPERTY()
    int32 statusCode;

    UPROPERTY()
    FString appID;

    UPROPERTY()
    FString Guid;

    UPROPERTY()
    FString message;
};