#pragma once

#include "Components/ActorComponent.h"
#include "ViveportType.h"
#include "ViveportIAPurchaseType.h"

#include "ViveportIAPSubscriptionListDemo.generated.h"


UCLASS( ClassGroup=(Viveport), meta=(BlueprintSpawnableComponent) )
class VIVEPORTSDK_API UViveportIAPSubscriptionListDemo : public UActorComponent
{
	GENERATED_BODY()

public:	
    // Called when the game starts
    void BeginPlay() override;

    void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    /** The APP ID and Key for IAP testing*/
    FString APP_ID = "4c6f0d0e-46f2-475b-881d-772521648c0d";
    FString APP_KEY ="Y4IlbGZ_T5KexTjrDtmkwNMKKEa1f0r4";

private:
    /** Callback objects */
    class MyViveportApiStatus : public ViveportApiStatus
    {
    protected:
        UViveportIAPSubscriptionListDemo* mDemo;
    public:
        void SetDemoPtr(UViveportIAPSubscriptionListDemo* p) { mDemo = p; }
    };

    class MyViveportIAPurchaseListener : public IAPurchaseListener
    {
    protected:
        UViveportIAPSubscriptionListDemo* mDemo;
    public:
        void SetDemoPtr(UViveportIAPSubscriptionListDemo* p) { mDemo = p; }
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

    class MyQuerySubscriptionListCallback : public MyViveportIAPurchaseListener
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

    MyQuerySubscriptionListCallback myQuerySubscriptionListCallback;


public:
    ViveportApiStatus* GetInitCallback() { return &myInitCallback; }
    ViveportApiStatus* GetShutdownCallback() { return &myShutdownCallback; }
    IAPurchaseListener* GetIsReadyCallback() { return &myIsReadyCallback; }
    IAPurchaseListener* GetQuerySubscriptionListCallback() { return &myQuerySubscriptionListCallback; }

};
