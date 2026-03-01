#include "ViveportIAPurchaseUserDataDemo.h"
#include "ViveportSDKPrivatePCH.h"
#include "ViveportApi.h"
#include "ViveportIAPurchase.h"

void UViveportIAPurchaseUserDataDemo::BeginPlay()
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

void UViveportIAPurchaseUserDataDemo::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    // Call ViveportApi::Shutdown()
    UViveportApi::Shutdown(&myShutdownCallback);
}

/***************************************************************
*					MyInitCallback
***************************************************************/

void UViveportIAPurchaseUserDataDemo::MyInitCallback::OnSuccess()
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchaseUserDataDemo][MyInitCallback] Init success."));
    FString fstring("Init success.");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    UViveportIAPurchase::IsReady(mDemo->GetIsReadyCallback(), mDemo->APP_KEY);
}

void UViveportIAPurchaseUserDataDemo::MyInitCallback::OnFailure(int nErrorCode)
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchaseUserDataDemo][MyInitCallback] Init failure. Error = %d"), nErrorCode);
    FString fstring = FString::Printf(TEXT("Init failure. Error = %d"), nErrorCode);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

/***************************************************************
*					MyShutdownCallback
***************************************************************/

void UViveportIAPurchaseUserDataDemo::MyShutdownCallback::OnSuccess()
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchaseUserDataDemo][MyShutdownCallback] Shutdown success."));
    FString fstring("Shutdown success.");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UViveportIAPurchaseUserDataDemo::MyShutdownCallback::OnFailure(int nErrorCode)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportIAPurchaseUserDataDemo][MyShutdownCallback] Shutdown failure. Error = %d"), nErrorCode);
    FString fstring = FString::Printf(TEXT("Shutdown failure. error=%d"), nErrorCode);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

/***************************************************************
*					MyIsReadyCallback
***************************************************************/

void UViveportIAPurchaseUserDataDemo::MyIsReadyCallback::OnSuccess(const FString& pchCurrencyName)
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchaseUserDataDemo][MyIsReadyCallback] IsReady success. Currency name = %s"), *pchCurrencyName);
    FString fstring = FString::Printf(TEXT("Is ready success, currency name = %s"), *pchCurrencyName);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    // Get balance
    UViveportIAPurchase::GetBalance(mDemo->GetBalanceCallback());
}

void UViveportIAPurchaseUserDataDemo::MyIsReadyCallback::OnFailure(int nCode, const FString& pchMessage)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportIAPurchaseUserDataDemo][MyIsReadyCallback] IsReady failure. Code = %d, message = %s"), nCode, *pchMessage);
    FString fstring = FString::Printf(TEXT("IsReady failure. Code = %d, message = %s"), nCode, *pchMessage);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

/***************************************************************
*					MyGetBalanceCallback
***************************************************************/

void UViveportIAPurchaseUserDataDemo::MyGetBalanceCallback::OnBalanceSuccess(const FString& pchBalance)
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchaseUserDataDemo][MyGetBalanceCallback] GetBalance success. Balance = %s"), *pchBalance);
    FString fstring = FString::Printf(TEXT("GetBalance success. Balance = %s"), *pchBalance);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    int32 balance = FCString::Atoi(*pchBalance);
    if (balance > 0)
    {
        //Request purchase with user data
        UViveportIAPurchase::Request(mDemo->GetRequestCallback(), "1", "Knife");
    }
}

void UViveportIAPurchaseUserDataDemo::MyGetBalanceCallback::OnFailure(int nCode, const FString& pchMessage)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportIAPurchaseUserDataDemo][MyGetBalanceCallback] GetBalance failure. Code = %d, message = %s"), nCode, *pchMessage);
    FString fstring = FString::Printf(TEXT("GetBalance failure. code = %d, message = %s"), nCode, *pchMessage);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

/***************************************************************
*					MyRequestCallback
***************************************************************/

void UViveportIAPurchaseUserDataDemo::MyRequestCallback::OnRequestSuccess(const FString& pchPurchaseId)
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchaseUserDataDemo][MyRequestCallback] Request success. Purchase id = %s"), *pchPurchaseId);
    FString fstring = FString::Printf(TEXT("Request success. Purchase id = %s"), *pchPurchaseId);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    // Query purchase
    UViveportIAPurchase::Purchase(mDemo->GetPurchaseCallback(), pchPurchaseId);
    //UViveportIAPurchase::Query(mDemo->GetQueryCallback(), pchPurchaseId);
}

void UViveportIAPurchaseUserDataDemo::MyRequestCallback::OnFailure(int nCode, const FString& pchMessage)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportIAPurchaseUserDataDemo][MyRequestCallback] Request failure. Code = %d, message = %s"), nCode, *pchMessage);
    FString fstring = FString::Printf(TEXT("Request failure. code = %d, message = %s"), nCode, *pchMessage);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

/***************************************************************
*					MyPurchaseCallback
***************************************************************/

void UViveportIAPurchaseUserDataDemo::MyPurchaseCallback::OnPurchaseSuccess(const FString& pchPurchaseId)
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchaseUserDataDemo][MyPurchaseCallback] Purchase success. Purchase id = %s"), *pchPurchaseId);
    FString fstring = FString::Printf(TEXT("Purchase success. Purchase id = %s"), *pchPurchaseId);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    // Query purchase
    UViveportIAPurchase::Query(mDemo->GetQueryCallback(), pchPurchaseId);
}

void UViveportIAPurchaseUserDataDemo::MyPurchaseCallback::OnFailure(int nCode, const FString& pchMessage)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportIAPurchaseUserDataDemo][MyPurchaseCallback] Purchase failure. Code = %d, message = %s"), nCode, *pchMessage);
    FString fstring = FString::Printf(TEXT("Purchase failure. Code = %d, message = %s"), nCode, *pchMessage);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

/***************************************************************
*					MyQueryCallback
***************************************************************/

void UViveportIAPurchaseUserDataDemo::MyQueryCallback::OnQuerySuccess(const FQueryResponse& response)
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchaseUserDataDemo][MyQueryCallback] Query success. Purchase id = %s"), *(response.purchase_id));
    FString fstring = FString::Printf(TEXT("Query success. Purchase id = %s"), *(response.purchase_id));
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UViveportIAPurchaseUserDataDemo::MyQueryCallback::OnFailure(int nCode, const FString& pchMessage)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportIAPurchaseUserDataDemo][MyQueryCallback] Query failure. Code = %d, message = %s"), nCode, *pchMessage);
    FString fstring = FString::Printf(TEXT("Query failure. Code = %d, message = %s"), nCode, *pchMessage);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}