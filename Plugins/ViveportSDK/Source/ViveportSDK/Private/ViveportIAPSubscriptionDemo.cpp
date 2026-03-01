#include "ViveportIAPSubscriptionDemo.h"
#include "ViveportSDKPrivatePCH.h"
#include "ViveportApi.h"
#include "ViveportIAPurchase.h"

void UViveportIAPSubscriptionDemo::BeginPlay()
{
    Super::BeginPlay();

    myInitCallback.SetDemoPtr(this);
    myShutdownCallback.SetDemoPtr(this);
    myIsReadyCallback.SetDemoPtr(this);
    myGetBalanceCallback.SetDemoPtr(this);
    myRequestSubscriptionPlanIDCallback.SetDemoPtr(this);
    mySubscribeCallback.SetDemoPtr(this);
    myQuerySubscriptionCallback.SetDemoPtr(this);

    // Call ViveportApi::Init()
    UViveportApi::Init(&myInitCallback, APP_ID);
}

void UViveportIAPSubscriptionDemo::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    // Call ViveportApi::Shutdown()
    UViveportApi::Shutdown(&myShutdownCallback);
}

/***************************************************************
*					MyInitCallback
***************************************************************/

void UViveportIAPSubscriptionDemo::MyInitCallback::OnSuccess()
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPSubscriptionDemo][MyInitCallback] Init success."));
    FString fstring("Init success.");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    UViveportIAPurchase::IsReady(mDemo->GetIsReadyCallback(), mDemo->APP_KEY);
}

void UViveportIAPSubscriptionDemo::MyInitCallback::OnFailure(int nErrorCode)
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPSubscriptionDemo][MyInitCallback] Init failure. Error = %d"), nErrorCode);
    FString fstring = FString::Printf(TEXT("Init failure. Error = %d"), nErrorCode);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

/***************************************************************
*					MyShutdownCallback
***************************************************************/

void UViveportIAPSubscriptionDemo::MyShutdownCallback::OnSuccess()
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPSubscriptionDemo][MyShutdownCallback] Shutdown success."));
    FString fstring("Shutdown success.");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UViveportIAPSubscriptionDemo::MyShutdownCallback::OnFailure(int nErrorCode)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportIAPSubscriptionDemo][MyShutdownCallback] Shutdown failure. Error = %d"), nErrorCode);
    FString fstring = FString::Printf(TEXT("Shutdown failure. error=%d"), nErrorCode);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

/***************************************************************
*					MyIsReadyCallback
***************************************************************/

void UViveportIAPSubscriptionDemo::MyIsReadyCallback::OnSuccess(const FString& pchCurrencyName)
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPSubscriptionDemo][MyIsReadyCallback] IsReady success. Currency name = %s"), *pchCurrencyName);
    FString fstring = FString::Printf(TEXT("Is ready success, currency name = %s"), *pchCurrencyName);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    // Get balance
    UViveportIAPurchase::GetBalance(mDemo->GetBalanceCallback());
}

void UViveportIAPSubscriptionDemo::MyIsReadyCallback::OnFailure(int nCode, const FString& pchMessage)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportIAPSubscriptionDemo][MyIsReadyCallback] IsReady failure. Code = %d, message = %s"), nCode, *pchMessage);
    FString fstring = FString::Printf(TEXT("IsReady failure. Code = %d, message = %s"), nCode, *pchMessage);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

/***************************************************************
*					MyGetBalanceCallback
***************************************************************/

void UViveportIAPSubscriptionDemo::MyGetBalanceCallback::OnBalanceSuccess(const FString& pchBalance)
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPSubscriptionDemo][MyGetBalanceCallback] GetBalance success. Balance = %s"), *pchBalance);
    FString fstring = FString::Printf(TEXT("GetBalance success. Balance = %s"), *pchBalance);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    int32 balance = FCString::Atoi(*pchBalance);
    if (balance > 0)
    {
        // Request subscription
        UViveportIAPurchase::RequestSubscriptionWithPlanID(mDemo->GetRequestSubscriptionPlanIDCallback(), mDemo->PLAN_ID);
    }
}

void UViveportIAPSubscriptionDemo::MyGetBalanceCallback::OnFailure(int nCode, const FString& pchMessage)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportIAPSubscriptionDemo][MyGetBalanceCallback] GetBalance failure. Code = %d, message = %s"), nCode, *pchMessage);
    FString fstring = FString::Printf(TEXT("GetBalance failure. code = %d, message = %s"), nCode, *pchMessage);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

/***************************************************************
*					MyRequestSubscriptionPlanIDCallback
***************************************************************/

void UViveportIAPSubscriptionDemo::MyRequestSubscriptionPlanIDCallback::OnRequestSubscriptionWithPlanIDSuccess(const FString& pchSubscriptionId)
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPSubscriptionDemo][MyRequestSubscriptionPlanIDCallback] Request subscription success. Subscription id = %s"), *pchSubscriptionId);
    FString fstring = FString::Printf(TEXT("Request subscription success. Subscription id = %s"), *pchSubscriptionId);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    // Subscribe the item
    UViveportIAPurchase::Subscribe(mDemo->GetSubscribeCallback(), pchSubscriptionId);
    //UViveportIAPurchase::QuerySubscription(mDemo->GetQuerySubscriptionCallback(), pchSubscriptionId);
}

void UViveportIAPSubscriptionDemo::MyRequestSubscriptionPlanIDCallback::OnFailure(int nCode, const FString& pchMessage)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportIAPSubscriptionDemo][MyRequestSubscriptionPlanIDCallback] Request subscription failure. Code = %d, message = %s"), nCode, *pchMessage);
    FString fstring = FString::Printf(TEXT("Request subscription failure. Code = %d, message = %s"), nCode, *pchMessage);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

/***************************************************************
*					MySubscribeCallback
***************************************************************/

void UViveportIAPSubscriptionDemo::MySubscribeCallback::OnSubscribeSuccess(const FString& pchSubscriptionId)
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPSubscriptionDemo][MySubscribeCallback] Subscribe success. Subscription id = %s"), *pchSubscriptionId);
    FString fstring = FString::Printf(TEXT("Subscribe success. Subscription id = %s"), *pchSubscriptionId);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    // Query subscription
    UViveportIAPurchase::QuerySubscription(mDemo->GetQuerySubscriptionCallback(), pchSubscriptionId);
}

void UViveportIAPSubscriptionDemo::MySubscribeCallback::OnFailure(int nCode, const FString& pchMessage)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportIAPSubscriptionDemo][MySubscribeCallback] Subscribe failure. Code = %d, message = %s"), nCode, *pchMessage);
    FString fstring = FString::Printf(TEXT("Subscribe failure. Code = %d, message = %s"), nCode, *pchMessage);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

/***************************************************************
*					MyQuerySubscriptionCallback
***************************************************************/

void UViveportIAPSubscriptionDemo::MyQuerySubscriptionCallback::OnQuerySubscriptionSuccess(const TArray<FSubscription>& subscriptionlist)
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPSubscriptionDemo][MyQuerySubscriptionCallback] Query subscription success."));
    FString fstring = FString::Printf(TEXT("Query subscription success."));
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UViveportIAPSubscriptionDemo::MyQuerySubscriptionCallback::OnFailure(int nCode, const FString& pchMessage)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportIAPSubscriptionDemo][MyQuerySubscriptionCallback] Query subscription failure. Code = %d, message = %s"), nCode, *pchMessage);
    FString fstring = FString::Printf(TEXT("Query subscription failure. Code = %d, message = %s"), nCode, *pchMessage);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}
