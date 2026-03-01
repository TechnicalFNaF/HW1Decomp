#pragma once

#include "Components/ActorComponent.h"
#include "ViveportType.h"
#include "ViveportIAPurchaseType.h"

#include "ViveportIAPurchaseUserDataDemo.generated.h"

UCLASS(ClassGroup = (Viveport), meta = (BlueprintSpawnableComponent))
class VIVEPORTSDK_API UViveportIAPurchaseUserDataDemo : public UActorComponent
{
    GENERATED_BODY()

public:
    // Called when the game starts
    void BeginPlay() override;

    void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    /** The APP ID and Key for IAP testing*/
    FString APP_ID = "e084bec3-74fb-4128-bda0-13feec9a9ed4";
    FString APP_KEY = "LXc8wYAuS_uT2IDF5SP6Vdb7lH22jmTs";

private:
    /** Callback objects */
    class MyViveportApiStatus : public ViveportApiStatus
    {
    protected:
        UViveportIAPurchaseUserDataDemo* mDemo;
    public:
        void SetDemoPtr(UViveportIAPurchaseUserDataDemo* p) { mDemo = p; }
    };

    class MyViveportIAPurchaseListener : public IAPurchaseListener
    {
    protected:
        UViveportIAPurchaseUserDataDemo* mDemo;
    public:
        void SetDemoPtr(UViveportIAPurchaseUserDataDemo* p) { mDemo = p; }
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

    class MyRequestCallback : public MyViveportIAPurchaseListener
    {
    public:
        void OnRequestSuccess(
            const FString& pchPurchaseId
        ) override;
        void OnFailure(
            int nCode,
            const FString& pchMessage
        ) override;
    };

    MyRequestCallback myRequestCallback;

    class MyPurchaseCallback : public MyViveportIAPurchaseListener
    {
    public:
        void OnPurchaseSuccess(
            const FString& pchPurchaseId
        ) override;
        void OnFailure(
            int nCode,
            const FString& pchMessage
        ) override;
    };

    MyPurchaseCallback myPurchaseCallback;

    class MyQueryCallback : public MyViveportIAPurchaseListener
    {
    public:
        void OnQuerySuccess(
            const FQueryResponse& response
        ) override;
        void OnFailure(
            int nCode,
            const FString& pchMessage
        ) override;
    };

    MyQueryCallback myQueryCallback;

public:
    ViveportApiStatus* GetInitCallback() { return &myInitCallback; }
    ViveportApiStatus* GetShutdownCallback() { return &myShutdownCallback; }
    IAPurchaseListener* GetIsReadyCallback() { return &myIsReadyCallback; }
    IAPurchaseListener* GetBalanceCallback() { return &myGetBalanceCallback; }
    IAPurchaseListener* GetRequestCallback() { return &myRequestCallback; }
    IAPurchaseListener* GetPurchaseCallback() { return &myPurchaseCallback; }
    IAPurchaseListener* GetQueryCallback() { return &myQueryCallback; }
};