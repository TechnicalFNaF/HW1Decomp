#include "ViveportIAPurchaseDemo.h"
#include "ViveportSDKPrivatePCH.h"
#include "ViveportApi.h"
#include "ViveportIAPurchase.h"

void UViveportIAPurchaseDemo::BeginPlay()
{
    Super::BeginPlay();

    myInitCallback.SetDemoPtr(this);
    myShutdownCallback.SetDemoPtr(this);
    myIsReadyCallback.SetDemoPtr(this);
    myGetBalanceCallback.SetDemoPtr(this);
    myRequestCallback.SetDemoPtr(this);
    myPurchaseCallback.SetDemoPtr(this);
    myQueryCallback.SetDemoPtr(this);

    // Call ViveportApi::Init()
    UViveportApi::Init(&myInitCallback, APP_ID);
}

void UViveportIAPurchaseDemo::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    // Call ViveportApi::Shutdown()
    UViveportApi::Shutdown(&myShutdownCallback);
}

/***************************************************************
*					MyInitCallback
***************************************************************/

void UViveportIAPurchaseDemo::MyInitCallback::OnSuccess()
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchaseDemo][MyInitCallback] Init success."));
    FString fstring("Init success.");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    UViveportIAPurchase::IsReady(mDemo->GetIsReadyCallback(), mDemo->APP_KEY);
}

void UViveportIAPurchaseDemo::MyInitCallback::OnFailure(int nErrorCode)
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchaseDemo][MyInitCallback] Init failure. Error = %d"), nErrorCode);
    FString fstring = FString::Printf(TEXT("Init failure. Error = %d"), nErrorCode);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

/***************************************************************
*					MyShutdownCallback
***************************************************************/

void UViveportIAPurchaseDemo::MyShutdownCallback::OnSuccess()
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchaseDemo][MyShutdownCallback] Shutdown success."));
    FString fstring("Shutdown success.");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UViveportIAPurchaseDemo::MyShutdownCallback::OnFailure(int nErrorCode)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportIAPurchaseDemo][MyShutdownCallback] Shutdown failure. Error = %d"), nErrorCode);
    FString fstring = FString::Printf(TEXT("Shutdown failure. error=%d"), nErrorCode);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

/***************************************************************
*					MyIsReadyCallback
***************************************************************/

void UViveportIAPurchaseDemo::MyIsReadyCallback::OnSuccess(const FString& pchCurrencyName)
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchaseDemo][MyIsReadyCallback] IsReady success. Currency name = %s"), *pchCurrencyName);
    FString fstring = FString::Printf(TEXT("Is ready success, currency name = %s"), *pchCurrencyName);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    // Get balance
    UViveportIAPurchase::GetBalance(mDemo->GetBalanceCallback());
}

void UViveportIAPurchaseDemo::MyIsReadyCallback::OnFailure(int nCode, const FString& pchMessage)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportIAPurchaseDemo][MyIsReadyCallback] IsReady failure. Code = %d, message = %s"), nCode, *pchMessage);
    FString fstring = FString::Printf(TEXT("IsReady failure. Code = %d, message = %s"), nCode, *pchMessage);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

/***************************************************************
*					MyGetBalanceCallback
***************************************************************/

void UViveportIAPurchaseDemo::MyGetBalanceCallback::OnBalanceSuccess(const FString& pchBalance)
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchaseDemo][MyGetBalanceCallback] GetBalance success. Balance = %s"), *pchBalance);
    FString fstring = FString::Printf(TEXT("GetBalance success. Balance = %s"), *pchBalance);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    int32 balance = FCString::Atoi(*pchBalance);
    if (balance > 0)
    {
        // Request purchase
        UViveportIAPurchase::Request(mDemo->GetRequestCallback(), "1");
    }
}

void UViveportIAPurchaseDemo::MyGetBalanceCallback::OnFailure(int nCode, const FString& pchMessage)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportIAPurchaseDemo][MyGetBalanceCallback] GetBalance failure. Code = %d, message = %s"), nCode, *pchMessage);
    FString fstring = FString::Printf(TEXT("GetBalance failure. code = %d, message = %s"), nCode, *pchMessage);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

/***************************************************************
*					MyRequestCallback
***************************************************************/

void UViveportIAPurchaseDemo::MyRequestCallback::OnRequestSuccess(const FString& pchPurchaseId)
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchaseDemo][MyRequestCallback] Request success. Purchase id = %s"), *pchPurchaseId);
    FString fstring = FString::Printf(TEXT("Request success. Purchase id = %s"), *pchPurchaseId);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    // Query purchase
    UViveportIAPurchase::Purchase(mDemo->GetPurchaseCallback(), pchPurchaseId);
    //UViveportIAPurchase::Query(mDemo->GetQueryCallback(), pchPurchaseId);
}

void UViveportIAPurchaseDemo::MyRequestCallback::OnFailure(int nCode, const FString& pchMessage)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportIAPurchaseDemo][MyRequestCallback] Request failure. Code = %d, message = %s"), nCode, *pchMessage);
    FString fstring = FString::Printf(TEXT("Request failure. code = %d, message = %s"), nCode, *pchMessage);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

/***************************************************************
*					MyPurchaseCallback
***************************************************************/

void UViveportIAPurchaseDemo::MyPurchaseCallback::OnPurchaseSuccess(const FString& pchPurchaseId)
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchaseDemo][MyPurchaseCallback] Purchase success. Purchase id = %s"), *pchPurchaseId);
    FString fstring = FString::Printf(TEXT("Purchase success. Purchase id = %s"), *pchPurchaseId);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    // Query purchase
    UViveportIAPurchase::Query(mDemo->GetQueryCallback(), pchPurchaseId);
}

void UViveportIAPurchaseDemo::MyPurchaseCallback::OnFailure(int nCode, const FString& pchMessage)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportIAPurchaseDemo][MyPurchaseCallback] Purchase failure. Code = %d, message = %s"), nCode, *pchMessage);
    FString fstring = FString::Printf(TEXT("Purchase failure. Code = %d, message = %s"), nCode, *pchMessage);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

/***************************************************************
*					MyQueryCallback
***************************************************************/

void UViveportIAPurchaseDemo::MyQueryCallback::OnQuerySuccess(const FQueryResponse& response)
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchaseDemo][MyQueryCallback] Query success. Purchase id = %s"), *(response.purchase_id));
    FString fstring = FString::Printf(TEXT("Query success. Purchase id = %s"), *(response.purchase_id));
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UViveportIAPurchaseDemo::MyQueryCallback::OnFailure(int nCode, const FString& pchMessage)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportIAPurchaseDemo][MyQueryCallback] Query failure. Code = %d, message = %s"), nCode, *pchMessage);
    FString fstring = FString::Printf(TEXT("Query failure. Code = %d, message = %s"), nCode, *pchMessage);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}