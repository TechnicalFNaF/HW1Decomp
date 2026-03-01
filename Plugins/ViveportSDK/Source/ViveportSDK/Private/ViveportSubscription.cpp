// Fill out your copyright notice in the Description page of Project Settings.

#include "ViveportSubscription.h"
#include "ViveportSDKPrivatePCH.h"
#include "viveport_api.h"
#include "viveport_ext_api.h"
#include <string>

void IsSubscriptionReadyHandler(int nResult, const char* message);

static ViveportApiStatus2* is_ready_callback;

void UViveportSubscription::IsReady(ViveportApiStatus2* callback)
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        is_ready_callback = callback;

        ViveportSubscription()->IsReady(IsSubscriptionReadyHandler);
    }
#elif PLATFORM_ANDROID
    static ViveportApiStatus2* cb = callback;
    ViveportCallback::OnResult onResult =
        [](int code, std::string message)
    {
        if (code == 0)
            cb->OnSuccess("0");
        else
            cb->OnFailure(code, FString(message.c_str()));
    };
    
    ViveportSubscription::IsReady(onResult);
#endif
}

bool UViveportSubscription::IsWindowsSubscriber()
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        return ViveportSubscription()->IsWindowsSubscriber();
    }
#elif PLATFORM_ANDROID
    return ViveportSubscription::IsWindowsSubscriber();
#endif
    return 0;
}

bool UViveportSubscription::IsAndroidSubscriber()
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        return ViveportSubscription()->IsAndroidSubscriber();
    }
#elif PLATFORM_ANDROID
    return ViveportSubscription::IsAndroidSubscriber();
#endif
    return 0;
}

SubscriptionTransactionType UViveportSubscription::GetTransactionType()
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        ESubscriptionTransactionType curT = ViveportSubscription()->GetTransactionType();
        switch (curT)
        {
            case UNKNOWN:
                return SubscriptionTransactionType::UNKNOWN;
                break;
            case PAID:
                return SubscriptionTransactionType::PAID;
                break;
            case REDEEM:
                return SubscriptionTransactionType::REDEEM;
                break;
            case FREE_TRIAL:
                return SubscriptionTransactionType::FREETRIAL;
                break;
            default:
                return SubscriptionTransactionType::UNKNOWN;
                break;
        }
    }
#elif PLATFORM_ANDROID
        int curT = ViveportSubscription::GetTransactionType();
        switch (curT)
        {
            case 0:
                return SubscriptionTransactionType::UNKNOWN;
                break;
            case 1:
                return SubscriptionTransactionType::PAID;
                break;
            case 2:
                return SubscriptionTransactionType::REDEEM;
                break;
            case 3:
                return SubscriptionTransactionType::FREETRIAL;
                break;
            default:
                return SubscriptionTransactionType::UNKNOWN;
                break;
        }
#endif
    return SubscriptionTransactionType::UNKNOWN;
}

void IsSubscriptionReadyHandler(int nResult, const char* message)
{
    if (nResult == 0)
    {
        UE_LOG(LogTemp, Display, TEXT("IsSubscriptionReady success: %s"), *FString(UTF8_TO_TCHAR(std::string(message).c_str())));
        is_ready_callback->OnSuccess(FString(message));
    }
    else
    {
        UE_LOG(LogTemp, Display, TEXT("Get IsSubscriptionReady, code: %d, msg: %s"), nResult, *FString(UTF8_TO_TCHAR(std::string(message).c_str())));
        is_ready_callback->OnFailure(nResult, FString(message));
    }
}