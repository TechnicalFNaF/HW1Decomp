#include "ViveportIAPQueryPurchaseListDemo.h"
#include "ViveportSDKPrivatePCH.h"
#include "ViveportApi.h"
#include "ViveportIAPurchase.h"

void UViveportIAPQueryPurchaseListDemo::BeginPlay()
{
    Super::BeginPlay();

    myInitCallback.SetDemoPtr(this);
    myShutdownCallback.SetDemoPtr(this);
    myIsReadyCallback.SetDemoPtr(this);
    myRequestCallback.SetDemoPtr(this);
    myQueryCallback.SetDemoPtr(this);

    // Call ViveportApi::Init()
    UViveportApi::Init(&myInitCallback, APP_ID);
}

void UViveportIAPQueryPurchaseListDemo::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    // Call ViveportApi::Shutdown()
    UViveportApi::Shutdown(&myShutdownCallback);
}

/***************************************************************
*					MyInitCallback
***************************************************************/

void UViveportIAPQueryPurchaseListDemo::MyInitCallback::OnSuccess()
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPQueryPurchaseListDemo][MyInitCallback] Init success."));
    FString fstring("Init success.");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    UViveportIAPurchase::IsReady(mDemo->GetIsReadyCallback(), mDemo->APP_KEY);
}

void UViveportIAPQueryPurchaseListDemo::MyInitCallback::OnFailure(int nErrorCode)
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPQueryPurchaseListDemo][MyInitCallback] Init failure. Error = %d"), nErrorCode);
    FString fstring = FString::Printf(TEXT("Init failure. Error = %d"), nErrorCode);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

/***************************************************************
*					MyShutdownCallback
***************************************************************/

void UViveportIAPQueryPurchaseListDemo::MyShutdownCallback::OnSuccess()
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPQueryPurchaseListDemo][MyShutdownCallback] Shutdown success."));
    FString fstring("Shutdown success.");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UViveportIAPQueryPurchaseListDemo::MyShutdownCallback::OnFailure(int nErrorCode)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportIAPQueryPurchaseListDemo][MyShutdownCallback] Shutdown failure. Error = %d"), nErrorCode);
    FString fstring = FString::Printf(TEXT("Shutdown failure. error=%d"), nErrorCode);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

/***************************************************************
*					MyIsReadyCallback
***************************************************************/

void UViveportIAPQueryPurchaseListDemo::MyIsReadyCallback::OnSuccess(const FString& pchCurrencyName)
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPQueryPurchaseListDemo][MyIsReadyCallback] IsReady success. Currency name = %s"), *pchCurrencyName);
    FString fstring = FString::Printf(TEXT("Is ready success, currency name = %s"), *pchCurrencyName);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    UViveportIAPurchase::Query(mDemo->GetQueryCallback());
}

void UViveportIAPQueryPurchaseListDemo::MyIsReadyCallback::OnFailure(int nCode, const FString& pchMessage)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportIAPQueryPurchaseListDemo][MyIsReadyCallback] IsReady failure. Code = %d, message = %s"), nCode, *pchMessage);
    FString fstring = FString::Printf(TEXT("IsReady failure. Code = %d, message = %s"), nCode, *pchMessage);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

/***************************************************************
*					MyRequestCallback
***************************************************************/

void UViveportIAPQueryPurchaseListDemo::MyRequestCallback::OnRequestSuccess(const FString& pchPurchaseId)
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPQueryPurchaseListDemo][MyRequestCallback] Request success. Purchase id = %s"), *pchPurchaseId);
    FString fstring = FString::Printf(TEXT("Request success. Purchase id = %s"), *pchPurchaseId);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UViveportIAPQueryPurchaseListDemo::MyRequestCallback::OnFailure(int nCode, const FString& pchMessage)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportIAPQueryPurchaseListDemo][MyRequestCallback] Request failure. Code = %d, message = %s"), nCode, *pchMessage);
    FString fstring = FString::Printf(TEXT("Request failure. code = %d, message = %s"), nCode, *pchMessage);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

/***************************************************************
*					MyQueryCallback
***************************************************************/

void UViveportIAPQueryPurchaseListDemo::MyQueryCallback::OnQuerySuccess(const FQueryListResponse& response)
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportIAPQueryPurchaseListDemo][MyQueryListCallback] Query success. total = %d, from = %d, to = %d"),
        response.total, response.from, response.to);
    FString fstring = FString::Printf(TEXT("Query success. total = %d, from = %d, to = %d"), response.total, response.from, response.to);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    for (int i = 0; i < response.purchaseList.Num(); i++) {
        UE_LOG(ViveportSDK, Log, TEXT("order_id = %s, app_id = %s, purchase_id = %s, price = %s, currency = %s, paid_timestamp = %lld, user_data = %s"),
            *response.purchaseList[i].order_id, *response.purchaseList[i].app_id, *response.purchaseList[i].purchase_id,
            *response.purchaseList[i].price, *response.purchaseList[i].currency, response.purchaseList[i].paid_timestamp,
            *response.purchaseList[i].user_data);
        fstring = FString::Printf(TEXT("purchase_id = %s, user_data = %s"),
            *response.purchaseList[i].purchase_id,
            *response.purchaseList[i].user_data);
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
    }
}

void UViveportIAPQueryPurchaseListDemo::MyQueryCallback::OnFailure(int nCode, const FString& pchMessage)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportIAPQueryPurchaseListDemo][MyQueryCallback] Query failure. Code = %d, message = %s"), nCode, *pchMessage);
    FString fstring = FString::Printf(TEXT("Query failure. Code = %d, message = %s"), nCode, *pchMessage);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}