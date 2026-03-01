// Fill out your copyright notice in the Description page of Project Settings.

#include "ViveportDeeplink.h"
#include "ViveportSDKPrivatePCH.h"
#include "viveport_api.h"
#include "viveport_ext_api.h"

#if PLATFORM_ANDROID
#include "Runtime/ApplicationCore/Public/Android/AndroidApplication.h"
#include "Runtime/Launch/Public/Android/AndroidJNI.h"
#endif

void DeeplinkIsReadyHandler(int nResult);
void GoToAppHandler(int nResult, const char* message);
void GoToStoreHandler(int nResult, const char* message);
void GoToAppOrGoToStoreHandler(int nResult, const char* message);

static ViveportApiStatus* isReady_callback;
static ViveportApiStatus2* goToApp_callback;
static ViveportApiStatus2* goToStore_callback;
static ViveportApiStatus2* goToAppOrGoToStore_callback;

static std::string s_deeplink_app_id;
static std::string s_launchData;
static std::string s_branchName;

void UViveportDeeplink::IsReady(ViveportApiStatus* callback)
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        isReady_callback = callback;

        ViveportDeeplink()->IsReady(DeeplinkIsReadyHandler);
}
#elif PLATFORM_ANDROID
    callback->OnSuccess();
#endif
}

void UViveportDeeplink::GoToApp(ViveportApiStatus2* callback, const FString viveportId, const FString launchData)
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        goToApp_callback = callback;
        s_deeplink_app_id = TCHAR_TO_UTF8(*viveportId);
        s_launchData = TCHAR_TO_UTF8(*launchData);
        ViveportDeeplink()->GoToApp(GoToAppHandler, s_deeplink_app_id.c_str(), s_launchData.c_str());
    }
#elif PLATFORM_ANDROID
    static ViveportApiStatus2* cb = callback;
    ViveportCallback2::OnSuccess onSuccess = 
        []()
    {
        cb->OnSuccess("0");
    };
    ViveportCallback2::OnFailure onFailure =
        [](int errorCode, std::string errorMessage)
    {
        cb->OnFailure(errorCode, *FString(errorMessage.c_str()));
    };

    ViveportDeeplink::GoToApp(
        onSuccess,
        onFailure,
        std::string(TCHAR_TO_UTF8(*viveportId)),
        std::string(TCHAR_TO_UTF8(*launchData)));
#endif
}

void UViveportDeeplink::GoToApp(ViveportApiStatus2* callback, const FString viveportId, const FString launchData, const FString branchName)
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        goToApp_callback = callback;
        s_deeplink_app_id = TCHAR_TO_UTF8(*viveportId);
        s_launchData = TCHAR_TO_UTF8(*launchData);
        s_branchName = TCHAR_TO_UTF8(*branchName);
        ViveportDeeplink()->GoToApp(GoToAppHandler, s_deeplink_app_id.c_str(), s_launchData.c_str(), s_branchName.c_str());
    }
#elif PLATFORM_ANDROID
    static ViveportApiStatus2* cb = callback;
    ViveportCallback2::OnSuccess onSuccess =
        []()
    {
        cb->OnSuccess("0");
    };
    ViveportCallback2::OnFailure onFailure =
        [](int errorCode, std::string errorMessage)
    {
        cb->OnFailure(errorCode, *FString(errorMessage.c_str()));
    };

    ViveportDeeplink::GoToApp(
        onSuccess,
        onFailure,
        std::string(TCHAR_TO_UTF8(*viveportId)),
        std::string(TCHAR_TO_UTF8(*launchData)));
#endif
}

void UViveportDeeplink::GoToStore(ViveportApiStatus2* callback, const FString viveportId)
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        goToStore_callback = callback;
        s_deeplink_app_id = TCHAR_TO_UTF8(*viveportId);
        ViveportDeeplink()->GoToStore(GoToStoreHandler, s_deeplink_app_id.c_str());
    }
#elif PLATFORM_ANDROID
    static ViveportApiStatus2* cb = callback;
    ViveportCallback2::OnSuccess onSuccess =
        []()
    {
        cb->OnSuccess("0");
    };
    ViveportCallback2::OnFailure onFailure =
        [](int errorCode, std::string errorMessage)
    {
        cb->OnFailure(errorCode, *FString(errorMessage.c_str()));
    };

    ViveportDeeplink::GoToStore(
        onSuccess,
        onFailure,
        std::string(TCHAR_TO_UTF8(*viveportId)));
#endif
}

void UViveportDeeplink::GoToAppOrGoToStore(ViveportApiStatus2* callback, const FString viveportId, const FString launchData)
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        goToAppOrGoToStore_callback = callback;
        s_deeplink_app_id = TCHAR_TO_UTF8(*viveportId);
        s_launchData = TCHAR_TO_UTF8(*launchData);
        ViveportDeeplink()->GoToAppOrGoToStore(GoToAppOrGoToStoreHandler, s_deeplink_app_id.c_str(), s_launchData.c_str());
    }
#elif PLATFORM_ANDROID
    static ViveportApiStatus2* cb = callback;
    ViveportCallback2::OnSuccess onSuccess =
        []()
    {
        cb->OnSuccess("0");
    };
    ViveportCallback2::OnFailure onFailure =
        [](int errorCode, std::string errorMessage)
    {
        cb->OnFailure(errorCode, *FString(errorMessage.c_str()));
    };

    ViveportDeeplink::GoToAppOrGoToStore(
        onSuccess,
        onFailure,
        std::string(TCHAR_TO_UTF8(*viveportId)),
        std::string(TCHAR_TO_UTF8(*launchData)));
#endif
}

FString UViveportDeeplink::GetAppLaunchData()
{
#if PLATFORM_WINDOWS
    auto appLaunchData = std::string("");
    if (FViveportSDKModule::IsAvailable())
    {
        char buf[256];
        int length = ViveportDeeplink()->GetAppLaunchData(buf, 256);
        appLaunchData.assign(buf, length);
    }
    FString fappLaunchData(UTF8_TO_TCHAR(appLaunchData.c_str()));
    return fappLaunchData;
#elif PLATFORM_ANDROID
    jobject activity = FAndroidApplication::GetGameActivityThis();
    std::string data = ViveportDeeplink::GetAppLaunchData(activity);
    return FString(data.c_str());
#endif
}

void DeeplinkIsReadyHandler(int nResult)
{
    if (nResult == 0)
    {
        UE_LOG(LogTemp, Display, TEXT("Deeplink_IsReady success"));
        isReady_callback->OnSuccess();
    }
    else
    {
        UE_LOG(LogTemp, Display, TEXT("Deeplink_IsReady, code: %d"), nResult);
        isReady_callback->OnFailure(nResult);
    }
}

void GoToAppHandler(int nResult, const char* message)
{
    if (nResult == 0)
    {
        UE_LOG(LogTemp, Display, TEXT("Deeplink_GoToApp success: %s"), *FString(UTF8_TO_TCHAR(std::string(message).c_str())));
        goToApp_callback->OnSuccess(FString(message));
    }
    else
    {
        UE_LOG(LogTemp, Display, TEXT("Deeplink_GoToApp, code: %d, msg: %s"), nResult, *FString(UTF8_TO_TCHAR(std::string(message).c_str())));
        goToApp_callback->OnFailure(nResult, FString(message));
    }
}

void GoToStoreHandler(int nResult, const char* message)
{
    if (nResult == 0)
    {
        UE_LOG(LogTemp, Display, TEXT("Deeplink_GoToStore success: %s"), *FString(UTF8_TO_TCHAR(std::string(message).c_str())));
        goToStore_callback->OnSuccess(FString(message));
    }
    else
    {
        UE_LOG(LogTemp, Display, TEXT("Deeplink_GoToStore, code: %d, msg: %s"), nResult, *FString(UTF8_TO_TCHAR(std::string(message).c_str())));
        goToStore_callback->OnFailure(nResult, FString(message));
    }
}

void GoToAppOrGoToStoreHandler(int nResult, const char* message)
{
    if (nResult == 0)
    {
        UE_LOG(LogTemp, Display, TEXT("Deeplink_GoToAppOrGoToStore success: %s"), *FString(UTF8_TO_TCHAR(std::string(message).c_str())));
        goToAppOrGoToStore_callback->OnSuccess(FString(message));
    }
    else
    {
        UE_LOG(LogTemp, Display, TEXT("Deeplink_GoToAppOrGoToStore, code: %d, msg: %s"), nResult, *FString(UTF8_TO_TCHAR(std::string(message).c_str())));
        goToAppOrGoToStore_callback->OnFailure(nResult, FString(message));
    }
}
