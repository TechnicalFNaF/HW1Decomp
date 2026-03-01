// Fill out your copyright notice in the Description page of Project Settings.

#include "ViveportIAPSubscriptionListDemo.h"
#include "ViveportSDKPrivatePCH.h"
#include "ViveportApi.h"
#include "ViveportIAPurchase.h"


// Called when the game starts
void UViveportIAPSubscriptionListDemo::BeginPlay()
{
	Super::BeginPlay();

    myInitCallback.SetDemoPtr(this);
    myShutdownCallback.SetDemoPtr(this);
    myIsReadyCallback.SetDemoPtr(this);
    myQuerySubscriptionListCallback.SetDemoPtr(this);

    // Call ViveportApi::Init()
    UViveportApi::Init(&myInitCallback, APP_ID);
	
}

void UViveportIAPSubscriptionListDemo::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    // Call ViveportApi::Shutdown()
    UViveportApi::Shutdown(&myShutdownCallback);
}

/***************************************************************
*					MyInitCallback
***************************************************************/

void UViveportIAPSubscriptionListDemo::MyInitCallback::OnSuccess()
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPSubscriptionListDemo][MyInitCallback] Init success."));
    FString fstring("Init success.");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    UViveportIAPurchase::IsReady(mDemo->GetIsReadyCallback(), mDemo->APP_KEY);
}

void UViveportIAPSubscriptionListDemo::MyInitCallback::OnFailure(int nErrorCode)
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPSubscriptionListDemo][MyInitCallback] Init failure. Error = %d"), nErrorCode);
    FString fstring = FString::Printf(TEXT("Init failure. Error = %d"), nErrorCode);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

/***************************************************************
*					MyShutdownCallback
***************************************************************/

void UViveportIAPSubscriptionListDemo::MyShutdownCallback::OnSuccess()
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPSubscriptionListDemo][MyShutdownCallback] Shutdown success."));
    FString fstring("Shutdown success.");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UViveportIAPSubscriptionListDemo::MyShutdownCallback::OnFailure(int nErrorCode)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportIAPSubscriptionListDemo][MyShutdownCallback] Shutdown failure. Error = %d"), nErrorCode);
    FString fstring = FString::Printf(TEXT("Shutdown failure. error=%d"), nErrorCode);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

/***************************************************************
*					MyIsReadyCallback
***************************************************************/

void UViveportIAPSubscriptionListDemo::MyIsReadyCallback::OnSuccess(const FString& pchCurrencyName)
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPSubscriptionListDemo][MyIsReadyCallback] IsReady success. Currency name = %s"), *pchCurrencyName);
    FString fstring = FString::Printf(TEXT("Is ready success, currency name = %s"), *pchCurrencyName);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    UViveportIAPurchase::QuerySubscriptionList(mDemo->GetQuerySubscriptionListCallback());
}

void UViveportIAPSubscriptionListDemo::MyIsReadyCallback::OnFailure(int nCode, const FString& pchMessage)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportIAPSubscriptionListDemo][MyIsReadyCallback] IsReady failure. Code = %d, message = %s"), nCode, *pchMessage);
    FString fstring = FString::Printf(TEXT("IsReady failure. Code = %d, message = %s"), nCode, *pchMessage);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

/***************************************************************
*					MyQuerySubscriptionListCallback
***************************************************************/

void UViveportIAPSubscriptionListDemo::MyQuerySubscriptionListCallback::OnQuerySubscriptionSuccess(const TArray<FSubscription>& subscriptionlist)
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPSubscriptionListDemo][MyQuerySubscriptionListCallback] Query subscriptionList success."));
    FString fstring = FString::Printf(TEXT("Query subscriptionList size = %d"), subscriptionlist.Num());
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
    
    for (int i = 0; i < subscriptionlist.Num(); i++)
    {
        UE_LOG(ViveportSDK, Log, TEXT("app_id = %s, subscription_id = %s, price = %s, currency = %s, plan_name = %s, plan_id = %s"),
            *subscriptionlist[i].app_id,
            *subscriptionlist[i].subscription_id,
            *subscriptionlist[i].price,
            *subscriptionlist[i].currency,
            *subscriptionlist[i].plan_name,
            *subscriptionlist[i].plan_id);

        fstring = FString::Printf(TEXT("subscription_id = %s, price = %s, currency = %s, plan_name = %s, plan_id = %s"),
            *subscriptionlist[i].subscription_id,
            *subscriptionlist[i].price,
            *subscriptionlist[i].currency,
            *subscriptionlist[i].plan_name,
            *subscriptionlist[i].plan_id);
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
    }
}

void UViveportIAPSubscriptionListDemo::MyQuerySubscriptionListCallback::OnFailure(int nCode, const FString& pchMessage)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportIAPSubscriptionListDemo][MyQuerySubscriptionCallback] Query subscriptionList failure. Code = %d, message = %s"), nCode, *pchMessage);
    FString fstring = FString::Printf(TEXT("Query subscriptionList failure. Code = %d, message = %s"), nCode, *pchMessage);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}


