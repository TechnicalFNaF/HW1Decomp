#include "ViveportArcadeSession.h"
#include "ViveportSDKPrivatePCH.h"
#include "ViveportSDK.h"
#include "ViveportArcadeSessionTypeInternal.h"
#include "JsonObjectConverter.h"
#include "viveport_api.h"

static SessionListener* Is_ready_listener;
static SessionListener* start_listener;
static SessionListener* stop_listener;

void SessionIsReadyHandler(int, const char *);
void StartHandler(int, const char *);
void StopHandler(int, const char *);

void UViveportArcadeSession::IsReady(SessionListener *listener)
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportArcadeSession][IsReady]"));
        Is_ready_listener = listener;
        ViveportArcadeSession()->IsReady(SessionIsReadyHandler);
    }
#elif PLATFORM_ANDROID
#endif
}

void UViveportArcadeSession::Start(SessionListener *listener)
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportArcadeSession][Start]"));
        start_listener = listener;
        ViveportArcadeSession()->Start(StartHandler);
    }
#elif PLATFORM_ANDROID
#endif
}

void UViveportArcadeSession::Stop(SessionListener *listener)
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportArcadeSession][Stop]"));
        stop_listener = listener;
        ViveportArcadeSession()->Stop(StopHandler);
    }
#elif PLATFORM_ANDROID
#endif
}

/***************************************************************
*						IsReady Handler
***************************************************************/

void SessionIsReadyHandler(int nCode, const char *pchMessage)
{
    FSessionIsReadyJsonResponse response;
    if (nCode == 0 && pchMessage != nullptr)
    {
        // Parse json message		
        response.statusCode = -1;	// handle the case of json parse error
        FJsonObjectConverter::JsonObjectStringToUStruct(pchMessage, &response, 0, 0);

        UE_LOG(ViveportSDK, Log, TEXT("[UViveportArcadeSession][SessionIsReadyHandler] status code: %d"), response.statusCode);
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportArcadeSession][SessionIsReadyHandler] message: %s"), *(response.message));
        if (response.statusCode == 0)
        {
            UE_LOG(ViveportSDK, Log, TEXT("[UViveportArcadeSession][SessionIsReadyHandler] appID: %s"), *(response.appID));
        }
    }

    if (Is_ready_listener != nullptr)
    {
        if (nCode == 0)
        {
            if (response.statusCode == 0)
            {
                Is_ready_listener->OnSuccess(response.appID);
            }
            else
            {
                Is_ready_listener->OnFailure(response.statusCode, response.message);
            }
        }
        else
        {
            FString jsonMessage = pchMessage;
            Is_ready_listener->OnFailure(nCode, jsonMessage);
        }
    }
}

/***************************************************************
*						StartHandler Handler
***************************************************************/

void StartHandler(int nCode, const char *pchMessage)
{
    FSessionJsonResponse response;
    if (nCode == 0 && pchMessage != nullptr)
    {
        // Parse json message		
        response.statusCode = -1;	// handle the case of json parse error
        FJsonObjectConverter::JsonObjectStringToUStruct(pchMessage, &response, 0, 0);

        // Print result
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportArcadeSession][StartHandler] status code: %d"), response.statusCode);
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportArcadeSession][StartHandler] message: %s"), *(response.message));
        if (response.statusCode == 0)
        {
            UE_LOG(ViveportSDK, Log, TEXT("[UViveportArcadeSession][StartHandler] appID: %s"), *(response.appID));
            UE_LOG(ViveportSDK, Log, TEXT("[UViveportArcadeSession][StartHandler] Guid: %s"), *(response.Guid));
        }
    }

    if (start_listener != nullptr)
    {
        if (nCode == 0)
        {
            if (response.statusCode == 0)
            {
                start_listener->OnStartSuccess(response.appID, response.Guid);
            }
            else
            {
                start_listener->OnFailure(response.statusCode, response.message);
            }
        }
        else
        {
            FString jsonMessage = pchMessage;
            start_listener->OnFailure(nCode, jsonMessage);
        }
    }
}

/***************************************************************
*						StopHandler Handler
***************************************************************/

void StopHandler(int nCode, const char *pchMessage)
{
    FSessionJsonResponse response;
    if (nCode == 0 && pchMessage != nullptr)
    {
        // Parse json message		
        response.statusCode = -1;	// handle the case of json parse error
        FJsonObjectConverter::JsonObjectStringToUStruct(pchMessage, &response, 0, 0);

        // Print result
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportArcadeSession][StopHandler] status code: %d"), response.statusCode);
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportArcadeSession][StopHandler] message: %s"), *(response.message));
        if (response.statusCode == 0)
        {
            UE_LOG(ViveportSDK, Log, TEXT("[UViveportArcadeSession][StopHandler] appID: %s"), *(response.appID));
            UE_LOG(ViveportSDK, Log, TEXT("[UViveportArcadeSession][StopHandler] Guid: %s"), *(response.Guid));
        }
    }

    if (stop_listener != nullptr)
    {
        if (nCode == 0)
        {
            if (response.statusCode == 0)
            {
                stop_listener->OnStopSuccess(response.appID, response.Guid);
            }
            else
            {
                stop_listener->OnFailure(response.statusCode, response.message);
            }
        }
        else
        {
            FString jsonMessage = pchMessage;
            stop_listener->OnFailure(nCode, jsonMessage);
        }
    }
}