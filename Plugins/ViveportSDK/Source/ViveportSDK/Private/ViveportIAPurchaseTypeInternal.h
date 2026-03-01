#pragma once

#include "CoreUObject.h"
#include "ViveportIAPurchaseType.h"
#include "ViveportIAPurchaseTypeInternal.generated.h"

/**
*	Json response of 'IsReady' API.
*/
USTRUCT()
struct FIsReadyJsonResponse
{
    GENERATED_BODY()

    UPROPERTY()
    int32 statusCode;

    UPROPERTY()
    FString currencyName;

    UPROPERTY()
    FString message;
};

/**
*	Json response of 'Request' API.
*/
USTRUCT()
struct FRequestJsonResponse
{
    GENERATED_BODY()

    UPROPERTY()
    int32 statusCode;

    UPROPERTY()
    FString purchase_id;

    UPROPERTY()
    FString message;
};

/**
*	Json response of 'Purchase' API.
*/
USTRUCT()
struct FPurchaseJsonResponse
{
    GENERATED_BODY()

    UPROPERTY()
    int32 statusCode;

    UPROPERTY()
    FString purchase_id;

    UPROPERTY()
    int64 paid_timestamp;

    UPROPERTY()
    FString message;
};

/**
*	Json response of 'Query' API.
*/
USTRUCT()
struct FQueryJsonResponse
{
    GENERATED_BODY()

    UPROPERTY()
    int32 statusCode;

    UPROPERTY()
    FString purchase_id;

    UPROPERTY()
    FString order_id;

    UPROPERTY()
    FString status;

    UPROPERTY()
    FString price;

    UPROPERTY()
    FString currency;

    UPROPERTY()
    int64 paid_timestamp;

    UPROPERTY()
    FString message;
};

/**
*	Json response of 'GetBalance' API.
*/
USTRUCT()
struct FGetBalanceJsonResponse
{
    GENERATED_BODY()

    UPROPERTY()
    int32 statusCode;

    UPROPERTY()
    FString currencyName;

    UPROPERTY()
    FString balance;

    UPROPERTY()
    FString message;
};

/**
*	Json response of 'Request Subscription' API.
*/
USTRUCT()
struct FRequestSubscriptionJsonResponse
{
    GENERATED_BODY()

    UPROPERTY()
    int32 statusCode;

    UPROPERTY()
    FString subscription_id;

    UPROPERTY()
    FString message;
};

/**
*	Json response of 'Subscribe' API.
*/
USTRUCT()
struct FSubscribeJsonResponse
{
    GENERATED_BODY()

    UPROPERTY()
    int32 statusCode;

    UPROPERTY()
    FString subscription_id;

    UPROPERTY()
    int64 subscribed_timestamp;

    UPROPERTY()
    FString plan_id;

    UPROPERTY()
    FString message;
};

/**
*	Json response of 'Query Subscribe' API.
*/

USTRUCT()
struct FQuerySubscriptionJsonResponse
{
    GENERATED_BODY()

    UPROPERTY()
    int32 statusCode;

    UPROPERTY()
    FString message;

    UPROPERTY()
    TArray<FSubscription> subscriptions;
};

/**
*	Json response of 'Cancel Subscribe' API.
*/

USTRUCT()
struct FCancelSubscriptionJsonResponse
{
    GENERATED_BODY()

    UPROPERTY()
    int32 statusCode;

    UPROPERTY()
    FString message;
};