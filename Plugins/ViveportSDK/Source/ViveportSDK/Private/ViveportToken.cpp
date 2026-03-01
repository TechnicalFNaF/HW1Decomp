// Fill out your copyright notice in the Description page of Project Settings.

#include "ViveportToken.h"
#include "ViveportSDKPrivatePCH.h"
#include "viveport_api.h"
#include "viveport_ext_api.h"
#include <string>

static ViveportApiStatus* is_token_ready_status;
static ViveportApiStatus2* get_session_token_status;

void IsTokenReadyHandler(int nResult);
void GetSessionTokenHandler(int nResult, const char* message);

void UViveportToken::IsReady(ViveportApiStatus *callback)
{
#if PLATFORM_WINDOWS
    int ret = 0;
    if (FViveportSDKModule::IsAvailable())
    {
        is_token_ready_status = callback;
        ViveportToken()->IsReady(IsTokenReadyHandler);
    }
#elif PLATFORM_ANDROID
    static ViveportApiStatus* cb = callback;
    ViveportCallback::OnResult onResult =
        [](int code, std::string message)
    {
        if (code == 0)
            cb->OnSuccess();
        else
            cb->OnFailure(code);
    };

    ViveportSessionToken::IsReady(onResult);
#else
#endif
}

void UViveportToken::GetSessionToken(ViveportApiStatus2 *callback)
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        get_session_token_status = callback;
        ViveportToken()->GetSessionToken(GetSessionTokenHandler);
    }
#elif PLATFORM_ANDROID
    static ViveportApiStatus2* cb = callback;
    ViveportCallback::OnResult onResult =
        [](int code, std::string message)
    {
        if (code == 0)
            cb->OnSuccess(FString(message.c_str()));
        else
            cb->OnFailure(code, FString(message.c_str()));
    };

    return ViveportSessionToken::GetSessionToken(onResult);
#else
#endif
}

void IsTokenReadyHandler(int nResult)
{
    return nResult == 0 ? is_token_ready_status->OnSuccess() : is_token_ready_status->OnFailure(nResult);
}

void GetSessionTokenHandler(int nResult, const char* message)
{
    if (nResult == 0)
    {
        UE_LOG(LogTemp, Display, TEXT("Session token: %s"), *FString(UTF8_TO_TCHAR(std::string(message).c_str())));
        get_session_token_status->OnSuccess(FString(message));
    }
    else
    {
        UE_LOG(LogTemp, Display, TEXT("Get session fail, code: %d, msg: %s"), nResult, *FString(UTF8_TO_TCHAR(std::string(message).c_str())));
        get_session_token_status->OnFailure(nResult, FString(message));
    }
}

