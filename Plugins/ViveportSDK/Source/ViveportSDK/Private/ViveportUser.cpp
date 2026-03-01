// Fill out your copyright notice in the Description page of Project Settings.

#include "ViveportUser.h"
#include "ViveportSDKPrivatePCH.h"
#include "viveport_api.h"
#include <string>

static ViveportApiStatus* user_is_ready_status;

void UserIsReadyHandler(int);

bool UViveportUser::IsReady(ViveportApiStatus *callback)
{
#if PLATFORM_WINDOWS
    int ret = 0;
    if (FViveportSDKModule::IsAvailable())
    {
        user_is_ready_status = callback;
        ret = ViveportUser()->IsReady(UserIsReadyHandler);
    }
    return ret == 1;
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

    return ((ViveportUser::IsReady(onResult) == 0) ? true : false);
#else
#endif
}

FString UViveportUser::GetUserID()
{
#if PLATFORM_WINDOWS
    auto userID = std::string("");
    if (FViveportSDKModule::IsAvailable())
    {
        char buf[256];
        int length = ViveportUser()->GetUserID(buf, 256);
        userID.assign(buf, length);
    }
    FString fUserID(UTF8_TO_TCHAR(userID.c_str()));
    return fUserID;
#elif PLATFORM_ANDROID
    return FString(UTF8_TO_TCHAR(ViveportUser::GetUserID().c_str()));
#else
#endif
}

FString UViveportUser::GetUserName()
{
#if PLATFORM_WINDOWS
    auto userName = std::string("");
    if (FViveportSDKModule::IsAvailable())
    {
        char buf[256];
        int length = ViveportUser()->GetUserName(buf, 256);
        userName.assign(buf, length);
    }
    FString fUserName(UTF8_TO_TCHAR(userName.c_str()));
    return fUserName;
#elif PLATFORM_ANDROID
    return FString(UTF8_TO_TCHAR(ViveportUser::GetUserName().c_str()));
#endif
}

FString UViveportUser::GetUserAvatarUrl()
{
#if PLATFORM_WINDOWS
    auto avatar = std::string("");
    if (FViveportSDKModule::IsAvailable())
    {
        char buf[256];
        int length = ViveportUser()->GetUserAvatarUrl(buf, 256);
        avatar.assign(buf, length);
    }
    FString fAvatar(UTF8_TO_TCHAR(avatar.c_str()));
    return fAvatar;
#elif PLATFORM_ANDROID
    return FString(UTF8_TO_TCHAR(ViveportUser::GetUserAvatar().c_str()));
#endif
}

void UserIsReadyHandler(int nResult)
{
    return nResult == 0 ? user_is_ready_status->OnSuccess() : user_is_ready_status->OnFailure(nResult);
}

