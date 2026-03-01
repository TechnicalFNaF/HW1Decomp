#pragma once

#include "Components/ActorComponent.h"
#include "ViveportType.h"
#include "ViveportIAPurchaseType.h"

#include "ViveportIAPSubscriptionDemo.generated.h"

UCLASS(ClassGroup = (Viveport), meta = (BlueprintSpawnableComponent))
class VIVEPORTSDK_API UViveportIAPSubscriptionDemo : public UActorComponent
{
    GENERATED_BODY()

public:
    // Called when the game starts
    void BeginPlay() override;

    void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    /** The APP ID and Key for IAP testing*/
    FString APP_ID = "3986c32c-64d4-4c5f-ab39-39afeb3fb6bf";
    FString APP_KEY = "KQ9VpxKkRg6n6_9k7zhXfeakaQmUAN48";

    /** The Plan ID of Subscription*/
    FString PLAN_ID = "PlanID";

private:
    /** Callback objects */
    class MyViveportApiStatus : public ViveportApiStatus
    {
    protected:
        UViveportIAPSubscriptionDemo* mDemo;
    public:
        void SetDemoPtr(UViveportIAPSubscriptionDemo* p) { mDemo = p; }
    };

    class MyViveportIAPurchaseListener : public IAPurchaseListener
    {
    protected:
        UViveportIAPSubscriptionDemo* mDemo;
    public:
        void SetDemoPtr(UViveportIAPSubscriptionDemo* p) { mDemo = p; }
    };

    class MyInitCallback : public MyViveportApiStatus
    {
    public:
        void OnSuccess(
        ) override;
        void OnFailure(
            int nErrorCode
        ) override;
    };

    MyInitCallback myInitCallback;

    class MyShutdownCallback : public MyViveportApiStatus
    {
    public:
        void OnSuccess(
        ) override;
        void OnFailure(
            int nErrorCode
        ) override;
    };

    MyShutdownCallback myShutdownCallback;

    class MyIsReadyCallback : public MyViveportIAPurchaseListener
    {
    public:
        void OnSuccess(
            const FString& pchCurrencyName
        ) override;
        void OnFailure(
            int nCode,
            const FString& pchMessage
        ) override;
    };

    MyIsReadyCallback myIsReadyCallback;

    class MyGetBalanceCallback : public MyViveportIAPurchaseListener
    {
    public:
        void OnBalanceSuccess(
            const FString& pchBalance
        ) override;
        void OnFailure(
            int nCode,
            const FString& pchMessage
        ) override;
    };

    MyGetBalanceCallback myGetBalanceCallback;

    class MyRequestSubscriptionPlanIDCallback : public MyViveportIAPurchaseListener
    {
    public:
        void OnRequestSubscriptionWithPlanIDSuccess(
            const FString& pchSubscriptionId
        ) override;
        void OnFailure(
            int nCode,
            const FString& pchMessage
        ) override;
    };

    MyRequestSubscriptionPlanIDCallback myRequestSubscriptionPlanIDCallback;

    class MySubscribeCallback : public MyViveportIAPurchaseListener
    {
    public:
        void OnSubscribeSuccess(
            const FString& pchSubscriptionId
        ) override;
        void OnFailure(
            int nCode,
            const FString& pchMessage
        ) override;
    };

    MySubscribeCallback mySubscribeCallback;

    class MyQuerySubscriptionCallback : public MyViveportIAPurchaseListener
    {
    public:
        void OnQuerySubscriptionSuccess(
            const TArray<FSubscription>& subscriptionlist
        ) override;
        void OnFailure(
            int nCode,
            const FString& pchMessage
        ) override;
    };

    MyQuerySubscriptionCallback myQuerySubscriptionCallback;

public:
    ViveportApiStatus* GetInitCallback() { return &myInitCallback; }
    ViveportApiStatus* GetShutdownCallback() { return &myShutdownCallback; }
    IAPurchaseListener* GetIsReadyCallback() { return &myIsReadyCallback; }
    IAPurchaseListener* GetBalanceCallback() { return &myGetBalanceCallback; }
    IAPurchaseListener* GetRequestSubscriptionPlanIDCallback() { return &myRequestSubscriptionPlanIDCallback; }
    IAPurchaseListener* GetSubscribeCallback() { return &mySubscribeCallback; }
    IAPurchaseListener* GetQuerySubscriptionCallback() { return &myQuerySubscriptionCallback; }
};