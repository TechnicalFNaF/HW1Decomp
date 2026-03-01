// Fill out your copyright notice in the Description page of Project Settings.

#include "ViveportIAPurchase.h"
#include "ViveportSDKPrivatePCH.h"
#include "ViveportSDK.h"
#include "ViveportIAPurchaseTypeInternal.h"
#include "JsonObjectConverter.h"
#include "viveport_api.h"

static IAPurchaseListener* is_ready_listener;
static IAPurchaseListener* request_listener;
static IAPurchaseListener* purchase_listener;
static IAPurchaseListener* query_listener;
static IAPurchaseListener* get_balance_listener;
static IAPurchaseListener* request_subscription_listener;
static IAPurchaseListener* request_subscription_plan_listener;
static IAPurchaseListener* subscribe_listener;
static IAPurchaseListener* query_subscription_listener;
static IAPurchaseListener* cancel_subscription_listener;

void IsReadyHandler(int, const char *);
void RequestHandler(int, const char *);
void PurchaseHandler(int, const char *);
void QueryHandler(int, const char *);
void QueryListHandler(int, const char *);
void GetBalanceHandler(int, const char *);
void RequestSubcriptionHandler(int, const char *);
void RequestSubcriptionWithPlanIdHandler(int, const char *);
void SubscribeHandler(int, const char *);
void QuerySubscriptionHandler(int, const char *);
void CancelSubscriptionHandler(int, const char *);

void UViveportIAPurchase::IsReady(IAPurchaseListener *listener, const FString& pchAppKey)
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][IsReady] app key = %s"), *pchAppKey);
        is_ready_listener = listener;
        ViveportIAPurchase()->IsReady(IsReadyHandler, TCHAR_TO_ANSI(*pchAppKey));
    }
#elif PLATFORM_ANDROID
    static IAPurchaseListener* lstnr = listener;
    ViveportCallback::OnResult onResult =
        [](int code, std::string message)
    {
        int64 statusCode = -1;
        FString currencyName;
        FString errMessage;

        if (code == 0)
        {
            TSharedPtr<FJsonObject> json_object;
            auto json_reader = TJsonReaderFactory<TCHAR>::Create(UTF8_TO_TCHAR(message.c_str()));
            if (FJsonSerializer::Deserialize(json_reader, json_object))
            {
                FString statusCodeStr = json_object->GetStringField("statusCode");
                statusCode = FCString::Atoi64(*statusCodeStr);
                errMessage = json_object->GetStringField("message");

                if (statusCode == 0)
                    currencyName = json_object->GetStringField("currencyName");
            }
        }

        if (lstnr != nullptr)
        {
            if (code == 0)
            {
                if (statusCode == 0)
                    lstnr->OnSuccess(currencyName);
                else
                    lstnr->OnFailure(statusCode, errMessage);
            }
            else
                lstnr->OnFailure(code, FString(message.c_str()));
        }
    };

    ViveportIAPurchase::IsReady(onResult, std::string(TCHAR_TO_UTF8(*pchAppKey)));
#else
#endif
}

void UViveportIAPurchase::Request(IAPurchaseListener *listener, const FString& pchPrice)
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][Request] price = %s"), *pchPrice);
        request_listener = listener;
        ViveportIAPurchase()->Request(RequestHandler, TCHAR_TO_ANSI(*pchPrice));
    }
#elif PLATFORM_ANDROID
    static IAPurchaseListener* lstnr = listener;
    ViveportCallback::OnResult onResult =
        [](int code, std::string message)
    {
        int64 statusCode = -1;
        FString purchaseId;
        FString errMessage;

        if (code == 0)
        {
            TSharedPtr<FJsonObject> json_object;
            auto json_reader = TJsonReaderFactory<TCHAR>::Create(UTF8_TO_TCHAR(message.c_str()));
            if (FJsonSerializer::Deserialize(json_reader, json_object))
            {
                FString statusCodeStr = json_object->GetStringField("statusCode");
                statusCode = FCString::Atoi64(*statusCodeStr);
                errMessage = json_object->GetStringField("message");

                if (statusCode == 0)
                    purchaseId = json_object->GetStringField("purchase_id");
            }
        }

        if (lstnr != nullptr)
        {
            if (code == 0)
            {
                if (statusCode == 0)
                    lstnr->OnRequestSuccess(purchaseId);
                else
                    lstnr->OnFailure(statusCode, errMessage);
            }
            else
                lstnr->OnFailure(code, FString(message.c_str()));
        }
    };
    ViveportIAPurchase::Request(onResult, std::string(TCHAR_TO_UTF8(*pchPrice)));
#else
#endif
}

void UViveportIAPurchase::Request(IAPurchaseListener *listener, const FString& pchPrice, const FString& pchUserData)
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][Request] price = %s, user_data = %s"), *pchPrice, *pchUserData);
        request_listener = listener;
        ViveportIAPurchase()->RequestWithUserData(RequestHandler, TCHAR_TO_ANSI(*pchPrice), TCHAR_TO_ANSI(*pchUserData));
    }
#elif PLATFORM_ANDROID
    static IAPurchaseListener* lstnr = listener;
    ViveportCallback::OnResult onResult =
        [](int code, std::string message)
    {
        int64 statusCode = -1;
        FString purchaseId;
        FString errMessage;

        if (code == 0)
        {
            TSharedPtr<FJsonObject> json_object;
            auto json_reader = TJsonReaderFactory<TCHAR>::Create(UTF8_TO_TCHAR(message.c_str()));
            if (FJsonSerializer::Deserialize(json_reader, json_object))
            {
                FString statusCodeStr = json_object->GetStringField("statusCode");
                statusCode = FCString::Atoi64(*statusCodeStr);
                errMessage = json_object->GetStringField("message");

                if (statusCode == 0)
                    purchaseId = json_object->GetStringField("purchase_id");
            }
        }

        if (lstnr != nullptr)
        {
            if (code == 0)
            {
                if (statusCode == 0)
                    lstnr->OnRequestSuccess(purchaseId);
                else
                    lstnr->OnFailure(statusCode, errMessage);
            }
            else
                lstnr->OnFailure(code, FString(message.c_str()));
        }
    };
    ViveportIAPurchase::Request(onResult, std::string(TCHAR_TO_UTF8(*pchPrice)), std::string(TCHAR_TO_UTF8(*pchUserData)));
#else
#endif
}

void UViveportIAPurchase::Purchase(IAPurchaseListener *listener, const FString& pchPurchaseId)
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][Purchase] purchase id = %s"), *pchPurchaseId);
        purchase_listener = listener;
        ViveportIAPurchase()->Purchase(PurchaseHandler, TCHAR_TO_ANSI(*pchPurchaseId));
    }
#elif PLATFORM_ANDROID
    static IAPurchaseListener* lstnr = listener;
    ViveportCallback::OnResult onResult =
        [](int code, std::string message)
    {
        int64 statusCode = -1;
        FString purchaseId;
        FString errMessage;

        if (code == 0)
        {
            TSharedPtr<FJsonObject> json_object;
            auto json_reader = TJsonReaderFactory<TCHAR>::Create(UTF8_TO_TCHAR(message.c_str()));
            if (FJsonSerializer::Deserialize(json_reader, json_object))
            {
                FString statusCodeStr = json_object->GetStringField("statusCode");
                statusCode = FCString::Atoi64(*statusCodeStr);
                errMessage = json_object->GetStringField("message");

                if (statusCode == 0)
                    purchaseId = json_object->GetStringField("purchase_id");
            }
        }

        if (lstnr != nullptr)
        {
            if (code == 0)
            {
                if (statusCode == 0)
                    lstnr->OnPurchaseSuccess(purchaseId);
                else
                    lstnr->OnFailure(statusCode, errMessage);
            }
            else
                lstnr->OnFailure(code, FString(message.c_str()));
        }
    };

    ViveportIAPurchase::MakePurchase(onResult, std::string(TCHAR_TO_UTF8(*pchPurchaseId)));
#else
#endif
}

void UViveportIAPurchase::Query(IAPurchaseListener *listener, const FString& pchPurchaseId)
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][Query] purchase id = %s"), *pchPurchaseId);
        query_listener = listener;
        ViveportIAPurchase()->Query(QueryHandler, TCHAR_TO_ANSI(*pchPurchaseId));
    }
#elif PLATFORM_ANDROID
    static IAPurchaseListener* lstnr = listener;
    ViveportCallback::OnResult onResult =
        [](int code, std::string message)
    {
        int64 statusCode = -1;
        FString purchaseId;
        FString errMessage;
        FString order_id;
        FString status;
        FString price;
        FString currency;
        int64 paid_timestamp = 0;

        if (code == 0)
        {
            TSharedPtr<FJsonObject> json_object;
            auto json_reader = TJsonReaderFactory<TCHAR>::Create(UTF8_TO_TCHAR(message.c_str()));
            if (FJsonSerializer::Deserialize(json_reader, json_object))
            {
                FString statusCodeStr = json_object->GetStringField("statusCode");
                statusCode = FCString::Atoi64(*statusCodeStr);
                errMessage = json_object->GetStringField("message");

                if (statusCode == 0)
                {
                    purchaseId = json_object->GetStringField("purchase_id");
                    order_id = json_object->GetStringField("order_id");
                    status = json_object->GetStringField("status");
                    price = json_object->GetStringField("price");
                    currency = json_object->GetStringField("currency");
                    FString paidTimestampStr = json_object->GetStringField("paid_timestamp");
                    paid_timestamp = FCString::Atoi64(*paidTimestampStr);
                }
            }
        }

        if (lstnr != nullptr)
        {
            if (code == 0)
            {
                if (statusCode == 0)
                {
                    FQueryResponse fQueryResponse;
                    fQueryResponse.purchase_id = purchaseId;
                    fQueryResponse.order_id = order_id;
                    fQueryResponse.status = status;
                    fQueryResponse.price = price;
                    fQueryResponse.currency = currency;
                    fQueryResponse.paid_timestamp = paid_timestamp;
                    lstnr->OnQuerySuccess(fQueryResponse);
                }
                else
                    lstnr->OnFailure(statusCode, errMessage);
            }
            else
                lstnr->OnFailure(code, FString(message.c_str()));
        }
    };

    ViveportIAPurchase::Query(onResult, std::string(TCHAR_TO_UTF8(*pchPurchaseId)));
#else
#endif
}

void UViveportIAPurchase::Query(IAPurchaseListener *listener)
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][QueryList]"));
        query_listener = listener;
        ViveportIAPurchase()->Query(QueryListHandler);
    }
#elif PLATFORM_ANDROID
    static IAPurchaseListener* lstnr = listener;
    ViveportCallback::OnResult onResult =
        [](int code, std::string message)
    {
        int64 statusCode = -1;
        int64 total = 0;
        int64 from = 0;
        int64 to = 0;
        FString errMessage;
        TArray<FQueryResponse2> purchaseList;

        if (code == 0)
        {
            TSharedPtr<FJsonObject> json_object;
            auto json_reader = TJsonReaderFactory<TCHAR>::Create(UTF8_TO_TCHAR(message.c_str()));
            if (FJsonSerializer::Deserialize(json_reader, json_object))
            {
                FString statusCodeStr = json_object->GetStringField("statusCode");
                statusCode = FCString::Atoi64(*statusCodeStr);
                errMessage = json_object->GetStringField("message");

                if (statusCode == 0)
                {
                    TSharedPtr<FJsonObject> purchaseData;
                    json_reader = TJsonReaderFactory<TCHAR>::Create(errMessage);
                    if (FJsonSerializer::Deserialize(json_reader, purchaseData))
                    {
                        total = purchaseData->GetIntegerField("total");
                        from = purchaseData->GetIntegerField("from");
                        to = purchaseData->GetIntegerField("to");
                        auto purchases = purchaseData->GetArrayField("purchases");
                        

                        for (int i = 0; i < purchases.Num(); i++)
                        {
                            FQueryResponse2 q;
                            q.app_id = purchases[i]->AsObject()->GetStringField("app_id");
                            q.currency = purchases[i]->AsObject()->GetStringField("currency");
                            q.purchase_id = purchases[i]->AsObject()->GetStringField("purchase_id");
                            q.order_id = purchases[i]->AsObject()->GetStringField("order_id");
                            q.price = purchases[i]->AsObject()->GetStringField("price");
                            q.user_data = purchases[i]->AsObject()->GetStringField("user_data");
                            q.paid_timestamp = FCString::Atoi64(*(purchases[i]->AsObject()->GetStringField("paid_timestamp")));
                            purchaseList.Add(q);
                        }
                    }
                }
            }
        }

        if (lstnr != nullptr)
        {
            if (code == 0)
            {
                if (statusCode == 0)
                {
                    FQueryListResponse response;
                    response.total = total;
                    response.from = from;
                    response.to = to;
                    response.purchaseList = purchaseList;
                    lstnr->OnQuerySuccess(response);
                }
                else
                    lstnr->OnFailure(statusCode, errMessage);
            }
            else
                lstnr->OnFailure(code, FString(message.c_str()));
        }
    };

    ViveportIAPurchase::Query(onResult);
#else
#endif
}

void UViveportIAPurchase::GetBalance(IAPurchaseListener *listener)
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][GetBalance]"));
        get_balance_listener = listener;
        ViveportIAPurchase()->GetBalance(GetBalanceHandler);
    }
#elif PLATFORM_ANDROID
    static IAPurchaseListener* lstnr = listener;
    ViveportCallback::OnResult onResult =
        [](int code, std::string message)
    {
        int64 statusCode = -1;
        FString balance;
        FString errMessage;

        if (code == 0)
        {
            TSharedPtr<FJsonObject> json_object;
            auto json_reader = TJsonReaderFactory<TCHAR>::Create(UTF8_TO_TCHAR(message.c_str()));
            if (FJsonSerializer::Deserialize(json_reader, json_object))
            {
                FString statusCodeStr = json_object->GetStringField("statusCode");
                statusCode = FCString::Atoi64(*statusCodeStr);
                errMessage = json_object->GetStringField("message");

                if (statusCode == 0)
                    balance = json_object->GetStringField("balance");
            }
        }

        if (lstnr != nullptr)
        {
            if (code == 0)
            {
                if (statusCode == 0)
                    lstnr->OnBalanceSuccess(balance);
                else
                    lstnr->OnFailure(statusCode, errMessage);
            }
            else
                lstnr->OnFailure(code, FString(message.c_str()));
        }
    };

    ViveportIAPurchase::GetBalance(onResult);
#else
#endif
}

void UViveportIAPurchase::RequestSubscription(IAPurchaseListener *listener, const FString& pchPrice, const FString& pchFreeTrialType, int nFreeTrialValue,
    const FString& pchChargePeriodType, int nChargePeriodValue, int nNumberOfChargePeriod, const FString& pchPlanId)
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][RequestSubscription] price = %s, plan id = %s"), *pchPrice, *pchPlanId);
        request_subscription_listener = listener;
        ViveportIAPurchase()->RequestSubscription(RequestSubcriptionHandler,
                                                TCHAR_TO_ANSI(*pchPrice),
                                                TCHAR_TO_ANSI(*pchFreeTrialType),
                                                nFreeTrialValue,
                                                TCHAR_TO_ANSI(*pchChargePeriodType),
                                                nChargePeriodValue,
                                                nNumberOfChargePeriod,
                                                TCHAR_TO_ANSI(*pchPlanId));
    }
#elif PLATFORM_ANDROID
    static IAPurchaseListener* lstnr = listener;
    ViveportCallback::OnResult onResult =
        [](int code, std::string message)
    {
        int64 statusCode = -1;
        FString subscription_id;
        FString errMessage;

        if (code == 0)
        {
            TSharedPtr<FJsonObject> json_object;
            auto json_reader = TJsonReaderFactory<TCHAR>::Create(UTF8_TO_TCHAR(message.c_str()));
            if (FJsonSerializer::Deserialize(json_reader, json_object))
            {
                FString statusCodeStr = json_object->GetStringField("statusCode");
                statusCode = FCString::Atoi64(*statusCodeStr);
                errMessage = json_object->GetStringField("message");

                if (statusCode == 0)
                    subscription_id = json_object->GetStringField("subscription_id");
            }
        }

        if (lstnr != nullptr)
        {
            if (code == 0)
            {
                if (statusCode == 0)
                    lstnr->OnRequestSubscriptionSuccess(subscription_id);
                else
                    lstnr->OnFailure(statusCode, errMessage);
            }
            else
                lstnr->OnFailure(code, FString(message.c_str()));
        }
    };

    ViveportIAPurchase::RequestSubscription(
        onResult,
        std::string(TCHAR_TO_UTF8(*pchPrice)),
        std::string(TCHAR_TO_UTF8(*pchFreeTrialType)),
        nFreeTrialValue,
        std::string(TCHAR_TO_UTF8(*pchChargePeriodType)),
        nChargePeriodValue,
        nNumberOfChargePeriod,
        std::string(TCHAR_TO_UTF8(*pchPlanId)));
#else
#endif
}

void UViveportIAPurchase::RequestSubscriptionWithPlanID(IAPurchaseListener *listener, const FString& pchPlanId)
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][RequestSubscriptionWithPlanID] plan id = %s"), *pchPlanId);
        request_subscription_plan_listener = listener;
        ViveportIAPurchase()->RequestSubscriptionWithPlanID(RequestSubcriptionWithPlanIdHandler, TCHAR_TO_ANSI(*pchPlanId));
    }
#elif PLATFORM_ANDROID
    static IAPurchaseListener* lstnr = listener;
    ViveportCallback::OnResult onResult =
        [](int code, std::string message)
    {
        int64 statusCode = -1;
        FString subscription_id;
        FString errMessage;

        if (code == 0)
        {
            TSharedPtr<FJsonObject> json_object;
            auto json_reader = TJsonReaderFactory<TCHAR>::Create(UTF8_TO_TCHAR(message.c_str()));
            if (FJsonSerializer::Deserialize(json_reader, json_object))
            {
                FString statusCodeStr = json_object->GetStringField("statusCode");
                statusCode = FCString::Atoi64(*statusCodeStr);
                errMessage = json_object->GetStringField("message");

                if (statusCode == 0)
                    subscription_id = json_object->GetStringField("subscription_id");
            }
        }

        if (lstnr != nullptr)
        {
            if (code == 0)
            {
                if (statusCode == 0)
                    lstnr->OnRequestSubscriptionWithPlanIDSuccess(subscription_id);
                else
                    lstnr->OnFailure(statusCode, errMessage);
            }
            else
                lstnr->OnFailure(code, FString(message.c_str()));
        }
    };

    ViveportIAPurchase::RequestSubscriptionWithPlanId(onResult, std::string(TCHAR_TO_UTF8(*pchPlanId)));
#else
#endif
}

void UViveportIAPurchase::Subscribe(IAPurchaseListener *listener, const FString& pchSubscriptionId)
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][Subscribe] subscription id = %s"), *pchSubscriptionId);
        subscribe_listener = listener;
        ViveportIAPurchase()->Subscribe(SubscribeHandler, TCHAR_TO_ANSI(*pchSubscriptionId));
    }
#elif PLATFORM_ANDROID
    static IAPurchaseListener* lstnr = listener;
    ViveportCallback::OnResult onResult =
        [](int code, std::string message)
    {
        int64 statusCode = -1;
        FString subscription_id;
        FString errMessage;

        if (code == 0)
        {
            TSharedPtr<FJsonObject> json_object;
            auto json_reader = TJsonReaderFactory<TCHAR>::Create(UTF8_TO_TCHAR(message.c_str()));
            if (FJsonSerializer::Deserialize(json_reader, json_object))
            {
                FString statusCodeStr = json_object->GetStringField("statusCode");
                statusCode = FCString::Atoi64(*statusCodeStr);
                errMessage = json_object->GetStringField("message");

                if (statusCode == 0)
                    subscription_id = json_object->GetStringField("subscription_id");
            }
    }

        if (lstnr != nullptr)
        {
            if (code == 0)
            {
                if (statusCode == 0)
                    lstnr->OnSubscribeSuccess(subscription_id);
                else
                    lstnr->OnFailure(statusCode, errMessage);
            }
            else
                lstnr->OnFailure(code, FString(message.c_str()));
        }
    };

    ViveportIAPurchase::SubScribe(onResult, std::string(TCHAR_TO_UTF8(*pchSubscriptionId)));
#else
#endif
}

void UViveportIAPurchase::QuerySubscription(IAPurchaseListener *listener, const FString& pchSubscriptionId)
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][QuerySubscription] subscription id = %s"), *pchSubscriptionId);
        query_subscription_listener = listener;
        ViveportIAPurchase()->QuerySubscription(QuerySubscriptionHandler, TCHAR_TO_ANSI(*pchSubscriptionId));
    }
#elif PLATFORM_ANDROID
    static IAPurchaseListener* lstnr = listener;
    ViveportCallback::OnResult onResult =
        [](int code, std::string message)
    {
        int64 statusCode = -1;
        FQuerySubscriptionJsonResponse response;
        FString errMessage;

        if (code == 0)
        {
            TSharedPtr<FJsonObject> json_object;
            auto json_reader = TJsonReaderFactory<TCHAR>::Create(UTF8_TO_TCHAR(message.c_str()));
            if (FJsonSerializer::Deserialize(json_reader, json_object))
            {
                FString statusCodeStr = json_object->GetStringField("statusCode");
                statusCode = FCString::Atoi64(*statusCodeStr);
                errMessage = json_object->GetStringField("message");

                if (statusCode == 0)
                {
                    FJsonObjectConverter::JsonObjectStringToUStruct(message.c_str(), &response, 0, 0);
                }
            }
        }

        if (lstnr != nullptr)
        {
            if (code == 0)
            {
                if (statusCode == 0)
                    lstnr->OnQuerySubscriptionSuccess(response.subscriptions);
                else
                    lstnr->OnFailure(statusCode, errMessage);
            }
            else
                lstnr->OnFailure(code, FString(message.c_str()));
        }
    };

    ViveportIAPurchase::QuerySubscription(onResult, std::string(TCHAR_TO_UTF8(*pchSubscriptionId)));
#else
#endif
}

void UViveportIAPurchase::QuerySubscriptionList(IAPurchaseListener *listener)
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][QuerySubscriptionList]"));
        query_subscription_listener = listener;
        ViveportIAPurchase()->QuerySubscriptionList(QuerySubscriptionHandler);
    }
#elif PLATFORM_ANDROID
    static IAPurchaseListener* lstnr = listener;
    ViveportCallback::OnResult onResult =
        [](int code, std::string message)
    {
        int64 statusCode = -1;
        FQuerySubscriptionJsonResponse response;
        FString errMessage;

        if (code == 0)
        {
            TSharedPtr<FJsonObject> json_object;
            auto json_reader = TJsonReaderFactory<TCHAR>::Create(UTF8_TO_TCHAR(message.c_str()));
            if (FJsonSerializer::Deserialize(json_reader, json_object))
            {
                FString statusCodeStr = json_object->GetStringField("statusCode");
                statusCode = FCString::Atoi64(*statusCodeStr);
                errMessage = json_object->GetStringField("message");

                if (statusCode == 0)
                {
                    FJsonObjectConverter::JsonObjectStringToUStruct(message.c_str(), &response, 0, 0);
                }
            }
        }

        if (lstnr != nullptr)
        {
            if (code == 0)
            {
                if (statusCode == 0)
                    lstnr->OnQuerySubscriptionSuccess(response.subscriptions);
                else
                    lstnr->OnFailure(statusCode, errMessage);
            }
            else
                lstnr->OnFailure(code, FString(message.c_str()));
        }
    };

    ViveportIAPurchase::QuerySubscriptionList(onResult);
#else
#endif
}

void UViveportIAPurchase::CancelSubscription(IAPurchaseListener *listener, const FString& pchSubscriptionId)
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][CancelSubscription] subscription id = %s"), *pchSubscriptionId);
        cancel_subscription_listener = listener;
        ViveportIAPurchase()->CancelSubscription(CancelSubscriptionHandler, TCHAR_TO_ANSI(*pchSubscriptionId));
    }
#elif PLATFORM_ANDROID
    static IAPurchaseListener* lstnr = listener;
    ViveportCallback::OnResult onResult =
        [](int code, std::string message)
    {
        int64 statusCode = -1;
        bool isCanceled = false;
        FString errMessage;

        if (code == 0)
        {
            TSharedPtr<FJsonObject> json_object;
            auto json_reader = TJsonReaderFactory<TCHAR>::Create(UTF8_TO_TCHAR(message.c_str()));
            if (FJsonSerializer::Deserialize(json_reader, json_object))
            {
                FString statusCodeStr = json_object->GetStringField("statusCode");
                statusCode = FCString::Atoi64(*statusCodeStr);
                errMessage = json_object->GetStringField("message");

                if (statusCode == 0)
                    isCanceled = true;
            }
        }

        if (lstnr != nullptr)
        {
            if (code == 0)
            {
                if (statusCode == 0)
                    lstnr->OnCancelSubscriptionSuccess(isCanceled);
                else
                    lstnr->OnFailure(statusCode, errMessage);
            }
            else
                lstnr->OnFailure(code, FString(message.c_str()));
        }
    };

    ViveportIAPurchase::CancelSubscription(onResult, std::string(TCHAR_TO_UTF8(*pchSubscriptionId)));
#else
#endif
}

/***************************************************************
*						IsReady Handler
***************************************************************/

void IsReadyHandler(int nCode, const char *pchMessage)
{
    FIsReadyJsonResponse response;
    if (nCode == 0 && pchMessage != nullptr)
    {
        // Parse json message		
        response.statusCode = -1;	// handle the case of json parse error
        FJsonObjectConverter::JsonObjectStringToUStruct(pchMessage, &response, 0, 0);

        UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][IsReadyHandler] status code: %d"), response.statusCode);
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][IsReadyHandler] message: %s"), *(response.message));
        if (response.statusCode == 0)
        {
            UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][IsReadyHandler] currency name: %s"), *(response.currencyName));
        }
    }

    if (is_ready_listener != nullptr)
    {
        if (nCode == 0)
        {
            if (response.statusCode == 0)
            {
                is_ready_listener->OnSuccess(response.currencyName);
            }
            else
            {
                is_ready_listener->OnFailure(response.statusCode, response.message);
            }
        }
        else
        {
            FString jsonMessage = pchMessage;
            is_ready_listener->OnFailure(nCode, jsonMessage);
        }
    }
}

/***************************************************************
*						Request Handler
***************************************************************/

void RequestHandler(int nCode, const char *pchMessage)
{
    FRequestJsonResponse response;
    if (nCode == 0 && pchMessage != nullptr)
    {
        // Parse json message		
        response.statusCode = -1;	// handle the case of json parse error
        FJsonObjectConverter::JsonObjectStringToUStruct(pchMessage, &response, 0, 0);

        // Print result
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][RequestHandler] status code: %d"), response.statusCode);
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][RequestHandler] message: %s"), *(response.message));
        if (response.statusCode == 0)
        {
            UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][RequestHandler] purchase id: %s"), *(response.purchase_id));
        }
    }

    if (request_listener != nullptr)
    {
        if (nCode == 0)
        {
            if (response.statusCode == 0)
            {
                request_listener->OnRequestSuccess(response.purchase_id);
            }
            else
            {
                request_listener->OnFailure(response.statusCode, response.message);
            }
        }
        else
        {
            FString jsonMessage = pchMessage;
            request_listener->OnFailure(nCode, jsonMessage);
        }
    }
}

/***************************************************************
*						Purchase Handler
***************************************************************/

void PurchaseHandler(int nCode, const char *pchMessage)
{
    FPurchaseJsonResponse response;
    if (nCode == 0 && pchMessage != nullptr)
    {
        // Parse json message		
        response.statusCode = -1;	// handle the case of json parse error
        FJsonObjectConverter::JsonObjectStringToUStruct(pchMessage, &response, 0, 0);

        // Print result
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][PurchaseHandler] status code: %d"), response.statusCode);
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][PurchaseHandler] message: %s"), *(response.message));
        if (response.statusCode == 0)
        {
            UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][PurchaseHandler] purchase id: %s"), *(response.purchase_id));
            UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][PurchaseHandler] paid timestamp: %lld"), response.paid_timestamp);
        }
    }

    if (purchase_listener != nullptr)
    {
        if (nCode == 0)
        {
            if (response.statusCode == 0)
            {
                purchase_listener->OnPurchaseSuccess(response.purchase_id);
            }
            else
            {
                purchase_listener->OnFailure(response.statusCode, response.message);
            }
        }
        else
        {
            FString jsonMessage = pchMessage;
            purchase_listener->OnFailure(nCode, jsonMessage);
        }
    }
}

/***************************************************************
*						Query Handler
****************************************************************/

void QueryHandler(int nCode, const char *pchMessage)
{
    FQueryJsonResponse response;
    if (nCode == 0 && pchMessage != nullptr)
    {
        // Parse json message		
        response.statusCode = -1;	// handle the case of json parse error
        FJsonObjectConverter::JsonObjectStringToUStruct(pchMessage, &response, 0, 0);

        // Print result
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][QueryHandler] status code: %d"), response.statusCode);
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][QueryHandler] message: %s"), *(response.message));
        if (response.statusCode == 0)
        {
            UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][QueryHandler] purchase id: %s"), *(response.purchase_id));
            UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][QueryHandler] order id: %s"), *(response.order_id));
            UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][QueryHandler] status: %s"), *(response.status));
            UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][QueryHandler] price: %s"), *(response.price));
            UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][QueryHandler] currency: %s"), *(response.currency));
            UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][QueryHandler] paid timestamp: %lld"), response.paid_timestamp);
        }
    }

    if (query_listener != nullptr)
    {
        if (nCode == 0)
        {
            if (response.statusCode == 0)
            {
                FQueryResponse result;
                result.purchase_id = response.purchase_id;
                result.order_id = response.order_id;
                result.status = response.status;
                result.price = response.price;
                result.currency = response.currency;
                result.paid_timestamp = response.paid_timestamp;

                query_listener->OnQuerySuccess(result);
            }
            else
            {
                query_listener->OnFailure(response.statusCode, response.message);
            }
        }
        else
        {
            FString jsonMessage = pchMessage;
            query_listener->OnFailure(nCode, jsonMessage);
        }
    }
}

/***************************************************************
*						Query List Handler
****************************************************************/

void QueryListHandler(int nCode, const char *pchMessage)
{
    int statusCode = -1;
    int total = 0;
    int from = 0;
    int to = 0;
    TArray<FQueryResponse2> purchaseList;
    FString message(pchMessage), message2;

    if (nCode == 0 && pchMessage != nullptr)
    {
        FString errorMessage = "";

        TSharedPtr<FJsonObject> JsonParsed;
        TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(message);
        if (FJsonSerializer::Deserialize(JsonReader, JsonParsed))
        {
            statusCode = JsonParsed->GetIntegerField("statusCode");
            message2 = JsonParsed->GetStringField("message");
        }

        if (statusCode == 0)
        {
            TSharedPtr<FJsonObject> JsonParsed2;
            TSharedRef<TJsonReader<TCHAR>> JsonReader2 = TJsonReaderFactory<TCHAR>::Create(message2);
            if (FJsonSerializer::Deserialize(JsonReader2, JsonParsed2))
            {
                total = JsonParsed2->GetIntegerField("total");
                from = JsonParsed2->GetIntegerField("from");
                to = JsonParsed2->GetIntegerField("to");
                
                TArray<TSharedPtr<FJsonValue>> objArray = JsonParsed2->GetArrayField("purchases");

                for (int32 i = 0; i < objArray.Num(); i++)
                {
                    TSharedPtr<FJsonObject> temp = objArray[i]->AsObject();

                    FQueryResponse2 fqr;
                    fqr.order_id = temp->GetStringField("order_id");
                    fqr.app_id = temp->GetStringField("app_id");
                    fqr.purchase_id = temp->GetStringField("purchase_id");
                    fqr.price = temp->GetStringField("price");
                    fqr.currency = temp->GetStringField("currency");
                    fqr.paid_timestamp = temp->GetNumberField("paid_timestamp");
                    fqr.user_data = temp->GetStringField("user_data");

                    purchaseList.Add(fqr);
                }
            }

        }
    }

    if (query_listener != nullptr)
    {
        if (nCode == 0)
        {
            if (statusCode == 0)
            {
                FQueryListResponse result;
                result.total = total;
                result.from = from;
                result.to = to;
                result.purchaseList = purchaseList;
                query_listener->OnQuerySuccess(result);
            }
            else
            {
                query_listener->OnFailure(statusCode, message2);
            }
        }
        else
        {
            query_listener->OnFailure(nCode, message);
        }
    }
}


/***************************************************************
*						Get Balance Handler
****************************************************************/

void GetBalanceHandler(int nCode, const char *pchMessage)
{
    FGetBalanceJsonResponse response;
    if (nCode == 0 && pchMessage != nullptr)
    {
        // Parse json message		
        response.statusCode = -1;	// handle the case of json parse error
        FJsonObjectConverter::JsonObjectStringToUStruct(pchMessage, &response, 0, 0);

        UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][GetBalanceHandler] status code: %d"), response.statusCode);
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][GetBalanceHandler] message: %s"), *(response.message));
        if (response.statusCode == 0)
        {
            UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][GetBalanceHandler] currency name: %s"), *(response.currencyName));
            UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][GetBalanceHandler] balance: %s"), *(response.balance));
        }
    }

    if (get_balance_listener != nullptr)
    {
        if (nCode == 0)
        {
            if (response.statusCode == 0)
            {
                get_balance_listener->OnBalanceSuccess(response.balance);
            }
            else
            {
                get_balance_listener->OnFailure(response.statusCode, response.message);
            }
        }
        else
        {
            FString jsonMessage = pchMessage;
            get_balance_listener->OnFailure(nCode, jsonMessage);
        }
    }
}

/***************************************************************
*					Request Subscription Handler
****************************************************************/

void RequestSubcriptionHandler(int nCode, const char *pchMessage)
{
    FRequestSubscriptionJsonResponse response;
    if (nCode == 0 && pchMessage != nullptr)
    {
        // Parse json message		
        response.statusCode = -1;	// handle the case of json parse error
        FJsonObjectConverter::JsonObjectStringToUStruct(pchMessage, &response, 0, 0);

        UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][RequestSubcriptionHandler] status code: %d"), response.statusCode);
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][RequestSubcriptionHandler] message: %s"), *(response.message));
        if (response.statusCode == 0)
        {
            UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][RequestSubcriptionHandler] subscription id: %s"), *(response.subscription_id));
        }
    }

    if (request_subscription_listener != nullptr)
    {
        if (nCode == 0)
        {
            if (response.statusCode == 0)
            {
                request_subscription_listener->OnRequestSubscriptionSuccess(response.subscription_id);
            }
            else
            {
                request_subscription_listener->OnFailure(response.statusCode, response.message);
            }
        }
        else
        {
            FString jsonMessage = pchMessage;
            request_subscription_listener->OnFailure(nCode, jsonMessage);
        }
    }
}

/***************************************************************
*			Request Subscription With Plan ID Handler
****************************************************************/

void RequestSubcriptionWithPlanIdHandler(int nCode, const char *pchMessage)
{
    FRequestSubscriptionJsonResponse response;
    if (nCode == 0 && pchMessage != nullptr)
    {
        // Parse json message		
        response.statusCode = -1;	// handle the case of json parse error
        FJsonObjectConverter::JsonObjectStringToUStruct(pchMessage, &response, 0, 0);

        UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][RequestSubcriptionWithPlanIdHandler] status code: %d"), response.statusCode);
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][RequestSubcriptionWithPlanIdHandler] message: %s"), *(response.message));
        if (response.statusCode == 0)
        {
            UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][RequestSubcriptionWithPlanIdHandler] subscription id: %s"), *(response.subscription_id));
        }
    }

    if (request_subscription_plan_listener != nullptr)
    {
        if (nCode == 0)
        {
            if (response.statusCode == 0)
            {
                request_subscription_plan_listener->OnRequestSubscriptionWithPlanIDSuccess(response.subscription_id);
            }
            else
            {
                request_subscription_plan_listener->OnFailure(response.statusCode, response.message);
            }
        }
        else
        {
            FString jsonMessage = pchMessage;
            request_subscription_plan_listener->OnFailure(nCode, jsonMessage);
        }
    }
}

/***************************************************************
*						Subscribe Handler
****************************************************************/

void SubscribeHandler(int nCode, const char *pchMessage)
{
    FSubscribeJsonResponse response;
    if (nCode == 0 && pchMessage != nullptr)
    {
        // Parse json message		
        response.statusCode = -1;	// handle the case of json parse error
        FJsonObjectConverter::JsonObjectStringToUStruct(pchMessage, &response, 0, 0);

        UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][SubscribeHandler] status code: %d"), response.statusCode);
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][SubscribeHandler] message: %s"), *(response.message));
        if (response.statusCode == 0)
        {
            UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][SubscribeHandler] subscription id: %s"), *(response.subscription_id));
            UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][SubscribeHandler] subscribed timestamp: %lld"), response.subscribed_timestamp);
            UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][SubscribeHandler] plan id: %s"), *(response.plan_id));
        }
    }

    if (subscribe_listener != nullptr)
    {
        if (nCode == 0)
        {
            if (response.statusCode == 0)
            {
                subscribe_listener->OnSubscribeSuccess(response.subscription_id);
            }
            else
            {
                subscribe_listener->OnFailure(response.statusCode, response.message);
            }
        }
        else
        {
            FString jsonMessage = pchMessage;
            subscribe_listener->OnFailure(nCode, jsonMessage);
        }
    }
}

/***************************************************************
*					Query Subscription Handler
****************************************************************/

void QuerySubscriptionHandler(int nCode, const char *pchMessage)
{
    FQuerySubscriptionJsonResponse response;
    if (nCode == 0 && pchMessage != nullptr)
    {
        // Parse json message		
        response.statusCode = -1;	// handle the case of json parse error
        FJsonObjectConverter::JsonObjectStringToUStruct(pchMessage, &response, 0, 0);

        UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][QuerySubscriptionHandler] status code: %d"), response.statusCode);
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][QuerySubscriptionHandler] message: %s"), *(response.message));
        if (response.statusCode == 0)
        {
            UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][QuerySubscriptionHandler] subscription count: %d"), response.subscriptions.Num());
            if (response.subscriptions.Num() > 0)
            {
                // Print first subscription
                FSubscription* subscription = &(response.subscriptions[0]);
                UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][QuerySubscriptionHandler] subscription id: %s"), *(subscription->subscription_id));
                UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][QuerySubscriptionHandler] orider id: %s"), *(subscription->order_id));
                UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][QuerySubscriptionHandler] price: %s"), *(subscription->price));
                UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][QuerySubscriptionHandler] currency: %s"), *(subscription->currency));
                UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][QuerySubscriptionHandler] subscribed timestamp: %lld"), subscription->subscribed_timestamp);
                UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][QuerySubscriptionHandler] plan id: %s"), *(subscription->plan_id));
                UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][QuerySubscriptionHandler] plan name: %s"), *(subscription->plan_name));
                UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][QuerySubscriptionHandler] status: %s"), *(subscription->status));
                UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][QuerySubscriptionHandler] free trial period: (%s, %d)"), *(subscription->free_trial_period.time_type), subscription->free_trial_period.value);
                UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][QuerySubscriptionHandler] charge period: (%s, %d)"), *(subscription->charge_period.time_type), subscription->charge_period.value);
                UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][QuerySubscriptionHandler] number of charge period: %d"), subscription->number_of_charge_period);
                UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][QuerySubscriptionHandler] status detail: (%lld, %s)"), subscription->status_detail.date_next_charge, *(subscription->status_detail.cancel_reason));
                if (subscription->status_detail.transactions.Num() > 0)
                {
                    FStatusDetailTransaction* transaction = &(subscription->status_detail.transactions[0]);
                    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][QuerySubscriptionHandler] status transaction: (%lld, %s, %s)"), transaction->create_time, *(transaction->payment_method), *(transaction->status));
                }
            }
        }
    }

    if (query_subscription_listener != nullptr)
    {
        if (nCode == 0)
        {
            if (response.statusCode == 0)
            {
                query_subscription_listener->OnQuerySubscriptionSuccess(response.subscriptions);
            }
            else
            {
                query_subscription_listener->OnFailure(response.statusCode, response.message);
            }
        }
        else
        {
            FString jsonMessage = pchMessage;
            query_subscription_listener->OnFailure(nCode, jsonMessage);
        }
    }
}

/***************************************************************
*					Cancel Subscription Handler
****************************************************************/

void CancelSubscriptionHandler(int nCode, const char *pchMessage)
{
    FCancelSubscriptionJsonResponse response;
    bool isCanceled = false;
    if (nCode == 0 && pchMessage != nullptr)
    {
        // Parse json message		
        response.statusCode = -1;	// handle the case of json parse error
        FJsonObjectConverter::JsonObjectStringToUStruct(pchMessage, &response, 0, 0);

        UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][CancelSubscriptionHandler] status code: %d"), response.statusCode);
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPurchase][CancelSubscriptionHandler] message: %s"), *(response.message));
        if (response.statusCode == 0)
        {
            isCanceled = true;
        }
    }

    if (cancel_subscription_listener != nullptr)
    {
        if (nCode == 0)
        {
            if (response.statusCode == 0)
            {
                cancel_subscription_listener->OnCancelSubscriptionSuccess(isCanceled);
            }
            else
            {
                cancel_subscription_listener->OnFailure(response.statusCode, response.message);
            }
        }
        else
        {
            FString jsonMessage = pchMessage;
            cancel_subscription_listener->OnFailure(nCode, jsonMessage);
        }
    }
}