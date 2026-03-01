// Fill out your copyright notice in the Description page of Project Settings.

#include "ViveportSubscriptionDemo.h"
#include "ViveportSDKPrivatePCH.h"

UViveportSubscriptionDemo::MyIsReadyCallback myIsReadyCallback;

// Called when the game starts
void UViveportSubscriptionDemo::BeginPlay()
{
    Super::BeginPlay();
    mySubscriptionInitCallback.SetDemoPtr(this);

    UViveportApi::Init(&mySubscriptionInitCallback, APP_ID);
}

void UViveportSubscriptionDemo::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    // Call ViveportApi::Shutdown()
    UViveportApi::Shutdown(&mySubscriptionShutdownCallback);
}


/***************************************************************
*					MySubscriptionInitCallback
***************************************************************/

void UViveportSubscriptionDemo::MySubscriptionInitCallback::OnSuccess()
{
    FString fstring("Init success.");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
    UViveportSubscription::IsReady(&myIsReadyCallback);
}

void UViveportSubscriptionDemo::MySubscriptionInitCallback::OnFailure(int error_code)
{
    FString fstring = FString::Printf(TEXT("Init failure. error=%d"), error_code);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

/***************************************************************
*					MySubscriptionShutdownCallback
***************************************************************/

void UViveportSubscriptionDemo::MySubscriptionShutdownCallback::OnSuccess()
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportSubscriptionDemo][MySubscriptionShutdownCallback] Shutdown success."));
    FString fstring("Shutdown success.");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UViveportSubscriptionDemo::MySubscriptionShutdownCallback::OnFailure(int error_code)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportSubscriptionDemo][MySubscriptionShutdownCallback] Shutdown failure. Error = %d"), error_code);
    FString fstring = FString::Printf(TEXT("Shutdown failure. error=%d"), error_code);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

/***************************************************************
*					MyIsReadyCallback
***************************************************************/

void UViveportSubscriptionDemo::MyIsReadyCallback::OnSuccess(const FString& result)
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportSubscriptionDemo][MyIsReadyCallback] IsReady success."));
    FString fstring = FString::Printf(TEXT("Is ready success"));
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    // Get IsWindowsSubscriber
    bool isWindowsSubscriber = UViveportSubscription::IsWindowsSubscriber();
    if (isWindowsSubscriber)
    {
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportSubscriptionDemo][IsWindowsSubscriber] User is a Windows subscriber"));
        fstring = FString::Printf(TEXT("User is a Windows subscriber"));
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
    }
    else
    {
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportSubscriptionDemo][IsWindowsSubscriber] User isn't a Windows subscriber"));
        fstring = FString::Printf(TEXT("User isn't a Windows subscriber"));
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
    }

    // Get IsAndroidSubscriber
    bool isAndoridSubscriber = UViveportSubscription::IsAndroidSubscriber();
    if (isAndoridSubscriber)
    {
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportSubscriptionDemo][IsAndroidSubscriber] User is a Andorid subscriber"));
        fstring = FString::Printf(TEXT("User is a Andorid subscriber"));
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
    }
    else
    {
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportSubscriptionDemo][IsAndroidSubscriber] User isn't a Andorid subscriber"));
        fstring = FString::Printf(TEXT("User isn't a Andorid subscriber"));
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
    }

    SubscriptionTransactionType transactionType = UViveportSubscription::GetTransactionType();

    switch (transactionType)
    {
        case SubscriptionTransactionType::UNKNOWN:
            UE_LOG(ViveportSDK, Log, TEXT("[UViveportSubscriptionDemo][GetTransactionType] TransactionType is Unknown"));
            fstring = FString::Printf(TEXT("TransactionType is Unknown"));
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
            break;
        case SubscriptionTransactionType::PAID:
            UE_LOG(ViveportSDK, Log, TEXT("[UViveportSubscriptionDemo][GetTransactionType] TransactionType is Paid"));
            fstring = FString::Printf(TEXT("TransactionType is Paid"));
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
            break;
        case SubscriptionTransactionType::REDEEM:
            UE_LOG(ViveportSDK, Log, TEXT("[UViveportSubscriptionDemo][GetTransactionType] TransactionType is Redeem"));
            fstring = FString::Printf(TEXT("TransactionType is Redeem"));
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
            break;
        case SubscriptionTransactionType::FREETRIAL:
            UE_LOG(ViveportSDK, Log, TEXT("[UViveportSubscriptionDemo][GetTransactionType] TransactionType is FreeTrial"));
            fstring = FString::Printf(TEXT("TransactionType is FreeTrial"));
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
            break;
        default:
            break;
    }
}

void UViveportSubscriptionDemo::MyIsReadyCallback::OnFailure(int error_code, const FString& error_message)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportSubscriptionDemo][MyIsReadyCallback] IsReady failure. Code = %d"), error_code);
    FString fstring = FString::Printf(TEXT("IsReady failure. Code = %d"), error_code);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}
