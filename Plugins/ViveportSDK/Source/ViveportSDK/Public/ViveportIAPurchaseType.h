#pragma once

#include "CoreUObject.h"
#include "ViveportIAPurchaseType.generated.h"

/**
*	Response of 'Query' API.
*/
USTRUCT()
struct FQueryResponse
{
    GENERATED_BODY()

    UPROPERTY()
    FString purchase_id;

    UPROPERTY()
    FString order_id;

    UPROPERTY()
    FString status;	//the value of status is "created" or "processing" or "success" or "failure" or "expired"

    UPROPERTY()
    FString price;

    UPROPERTY()
    FString currency;

    UPROPERTY()
    int64 paid_timestamp;
};

USTRUCT()
struct FQueryResponse2
{
    GENERATED_BODY()

    UPROPERTY()
    FString order_id;

    UPROPERTY()
    FString app_id;

    UPROPERTY()
    FString purchase_id;

    UPROPERTY()
    FString price;

    UPROPERTY()
    FString currency;

    UPROPERTY()
    int64 paid_timestamp;

    UPROPERTY()
    FString user_data;
};

USTRUCT()
struct FQueryListResponse
{
    GENERATED_BODY()

    UPROPERTY()
    int64 total;

    UPROPERTY()
    int64 from;

    UPROPERTY()
    int64 to;

    UPROPERTY()
    TArray<FQueryResponse2> purchaseList;
};

/**
*	Response of 'Query Subscription' API.
*/
USTRUCT()
struct FStatusDetailTransaction
{
    GENERATED_BODY()

    UPROPERTY()
    int64 create_time;

    UPROPERTY()
    FString payment_method;

    UPROPERTY()
    FString status;	// paymentFailed / pendingWebhook / finish
};

USTRUCT()
struct FStatusDetail
{
    GENERATED_BODY()

    UPROPERTY()
    int64 date_next_charge;

    UPROPERTY()
    TArray<FStatusDetailTransaction> transactions;

    UPROPERTY()
    FString cancel_reason;	// paymentFailed / pendingWebhook / finish
};


USTRUCT()
struct FTimePeriod
{
    GENERATED_BODY()

    UPROPERTY()
    FString time_type;

    UPROPERTY()
    int32 value;
};

USTRUCT()
struct FSubscription
{
    GENERATED_BODY()

    UPROPERTY()
    FString app_id;

    UPROPERTY()
    FString order_id;

    UPROPERTY()
    FString subscription_id;

    UPROPERTY()
    FString price;

    UPROPERTY()
    FString currency;

    UPROPERTY()
    int64 subscribed_timestamp;

    UPROPERTY()
    FTimePeriod free_trial_period;

    UPROPERTY()
    FTimePeriod charge_period;

    UPROPERTY()
    int32 number_of_charge_period;

    UPROPERTY()
    FString plan_id;

    UPROPERTY()
    FString plan_name;

    UPROPERTY()
    FString status;	//the value of status is "created" or "processing" or "failure" or "expired" or "ACTIVE" or "NON_RENEWING" or "CANCELED"

    UPROPERTY()
    FStatusDetail status_detail;
};

/**
*	Callback of In App Purchase APIs
*/
class IAPurchaseListener
{
public:
    virtual ~IAPurchaseListener() { }

    virtual void OnSuccess(const FString& pchCurrencyName) { }
    virtual	void OnRequestSuccess(const FString& pchPurchaseId) { }
    virtual void OnPurchaseSuccess(const FString& pchPurchaseId) { }
    virtual void OnQuerySuccess(const FQueryResponse& response) { }
    virtual void OnQuerySuccess(const FQueryListResponse& response) { }
    virtual void OnBalanceSuccess(const FString& pchBalance) { }
    virtual void OnRequestSubscriptionSuccess(const FString& pchSubscriptionId) { }
    virtual void OnRequestSubscriptionWithPlanIDSuccess(const FString& pchSubscriptionId) { }
    virtual void OnSubscribeSuccess(const FString& pchSubscriptionId) { }
    virtual void OnQuerySubscriptionSuccess(const TArray<FSubscription>& subscriptionlist) { }
    virtual void OnCancelSubscriptionSuccess(bool bCanceled) { }
    virtual void OnFailure(int nCode, const FString& pchMessage) { }

protected:
    IAPurchaseListener() { }
};