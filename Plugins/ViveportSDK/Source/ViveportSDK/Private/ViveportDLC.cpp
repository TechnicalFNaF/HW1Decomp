// Fill out your copyright notice in the Description page of Project Settings.

#include "ViveportDLC.h"
#include "ViveportSDKPrivatePCH.h"
#include "viveport_api.h"
#include "viveport_ext_api.h"

void IsDLCReadyHandler(int nResult);

static ViveportApiStatus* is_dlc_ready_callback;

int UViveportDLC::IsReady(ViveportApiStatus* callback)
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        is_dlc_ready_callback = callback;

        return ViveportDlc()->IsReady(IsDLCReadyHandler);
    }
#endif
    return 0;
}

int UViveportDLC::GetCount()
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        return ViveportDlc()->GetCount();
    }
#endif
    return -1;
}

bool UViveportDLC::GetIsAvailable(int index, FString &app_id, bool &isAvailable)
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        char* pchAppId = new char[37];
        bool isInRange = ViveportDlc()->GetIsAvailable(index, pchAppId, isAvailable);
        app_id = FString(pchAppId);

        return isInRange;
    }
#endif
    return false;
}

int UViveportDLC::IsSubscribed()
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        int errorCode = ViveportDlc()->IsSubscribed();
        
        return errorCode;
    }
#endif
    return 1;
}

void IsDLCReadyHandler(int nResult)
{
    return nResult == 0 ?
        is_dlc_ready_callback->OnSuccess() : 
        is_dlc_ready_callback->OnFailure(nResult);
}