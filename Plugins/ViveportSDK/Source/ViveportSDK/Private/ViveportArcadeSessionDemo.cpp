#include "ViveportArcadeSessionDemo.h"
#include "ViveportSDKPrivatePCH.h"
#include "ViveportApi.h"
#include "ViveportArcadeSession.h"

void UViveportArcadeSessionDemo::BeginPlay()
{
    Super::BeginPlay();

    myInitCallback.SetDemoPtr(this);
    myShutdownCallback.SetDemoPtr(this);
    myIsReadyCallback.SetDemoPtr(this);
    myStartSessionCallback.SetDemoPtr(this);
    myStopSessionCallback.SetDemoPtr(this);

    // Call ViveportApi::Init()
    UViveportApi::Init(&myInitCallback, APP_ID);
}

void UViveportArcadeSessionDemo::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    // Call ViveportApi::Shutdown()
    UViveportApi::Shutdown(&myShutdownCallback);
}

/***************************************************************
*					MyInitCallback
***************************************************************/

void UViveportArcadeSessionDemo::MyInitCallback::OnSuccess()
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportArcadeSessionDemo][MyInitCallback] Init success."));
    FString fstring("Init success.");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    UViveportArcadeSession::IsReady(mDemo->GetIsReadyCallback());
}

void UViveportArcadeSessionDemo::MyInitCallback::OnFailure(int nErrorCode)
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportArcadeSessionDemo][MyInitCallback] Init failure. Error = %d"), nErrorCode);
    FString fstring = FString::Printf(TEXT("Init failure. Error = %d"), nErrorCode);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

/***************************************************************
*					MyShutdownCallback
***************************************************************/

void UViveportArcadeSessionDemo::MyShutdownCallback::OnSuccess()
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportArcadeSessionDemo][MyShutdownCallback] Shutdown success."));
    FString fstring("Shutdown success.");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UViveportArcadeSessionDemo::MyShutdownCallback::OnFailure(int nErrorCode)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportArcadeSessionDemo][MyShutdownCallback] Shutdown failure. Error = %d"), nErrorCode);
    FString fstring = FString::Printf(TEXT("Shutdown failure. error=%d"), nErrorCode);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

/***************************************************************
*					MyIsReadyCallback
***************************************************************/

void UViveportArcadeSessionDemo::MyIsReadyCallback::OnSuccess(const FString& pchAppID)
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportArcadeSessionDemo][MyIsReadyCallback] IsReady success. app ID = %s"), *pchAppID);
    FString fstring = FString::Printf(TEXT("Is ready success, app ID = %s"), *pchAppID);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    // start session
    UViveportArcadeSession::Start(mDemo->GetStartSessionCallback());
}

void UViveportArcadeSessionDemo::MyIsReadyCallback::OnFailure(int nCode, const FString& pchMessage)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportArcadeSessionDemo][MyIsReadyCallback] IsReady failure. Code = %d, message = %s"), nCode, *pchMessage);
    FString fstring = FString::Printf(TEXT("IsReady failure. Code = %d, message = %s"), nCode, *pchMessage);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

/***************************************************************
*					MyStartSessionCallback
***************************************************************/

void UViveportArcadeSessionDemo::MyStartSessionCallback::OnStartSuccess(const FString& pchAppID, const FString& pchGuid)
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportArcadeSessionDemo][MyStartSessionCallback] start session success. pchAppID = %s, pchGuid = %s"), *pchAppID, *pchGuid);
    FString fstring = FString::Printf(TEXT("start session success. pchAppID = %s, pchGuid=%s"), *pchAppID, *pchGuid);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    UViveportArcadeSession::Stop(mDemo->GetStopSessionCallback());
}

void UViveportArcadeSessionDemo::MyStartSessionCallback::OnFailure(int nCode, const FString& pchMessage)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportArcadeSessionDemo][MyStartSessionCallback] start session failure. Code = %d, message = %s"), nCode, *pchMessage);
    FString fstring = FString::Printf(TEXT("start session failure. code = %d, message = %s"), nCode, *pchMessage);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

/***************************************************************
*					MyStopSessionCallback
***************************************************************/

void UViveportArcadeSessionDemo::MyStopSessionCallback::OnStopSuccess(const FString& pchAppID, const FString& pchGuid)
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportArcadeSessionDemo][MyStopSessionCallback] stop session success. pchAppID = %s, pchGuid = %s"), *pchAppID, *pchGuid);
    FString fstring = FString::Printf(TEXT("stop session success. pchAppID = %s, pchGuid=%s"), *pchAppID, *pchGuid);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

}

void UViveportArcadeSessionDemo::MyStopSessionCallback::OnFailure(int nCode, const FString& pchMessage)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportArcadeSessionDemo][MyStopSessionCallback] stop session failure. Code = %d, message = %s"), nCode, *pchMessage);
    FString fstring = FString::Printf(TEXT("stop session failure. code = %d, message = %s"), nCode, *pchMessage);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}