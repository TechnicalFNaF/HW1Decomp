// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreUObject.h"
#include "ViveportIAPurchaseType.h"
#include "ViveportIAPurchase.generated.h"

/**
 *	APIs of Viveport In-App Purchase SDK
 */
UCLASS()
class VIVEPORTSDK_API UViveportIAPurchase : public UObject
{
    GENERATED_BODY()

public:
    static void IsReady(IAPurchaseListener *listener, const FString& pchAppKey);
    static void Request(IAPurchaseListener *listener, const FString& pchPrice);
    static void Request(IAPurchaseListener *listener, const FString& pchPrice, const FString& pchUserData);
    static void Purchase(IAPurchaseListener *listener, const FString& pchPurchaseId);
    static void Query(IAPurchaseListener *listener, const FString& pchPurchaseId);
    static void Query(IAPurchaseListener *listener);
    static void GetBalance(IAPurchaseListener *listener);

    static void RequestSubscription(IAPurchaseListener *listener, const FString& pchPrice, const FString& pchFreeTrialType, int nFreeTrialValue,
        const FString& pchChargePeriodType, int nChargePeriodValue, int nNumberOfChargePeriod, const FString& pchPlanId);

    static void RequestSubscriptionWithPlanID(IAPurchaseListener *listener, const FString& pchPlanId);
    static void Subscribe(IAPurchaseListener *listener, const FString& pchSubscriptionId);
    static void QuerySubscription(IAPurchaseListener *listener, const FString& pchSubscriptionId);
    static void QuerySubscriptionList(IAPurchaseListener *listener);
    static void CancelSubscription(IAPurchaseListener *listener, const FString& pchSubscriptionId);
};


