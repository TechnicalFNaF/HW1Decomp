// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreUObject.h"
#include "ViveportType.h"
#include "ViveportSubscription.generated.h"

UENUM(BlueprintType)
enum class SubscriptionTransactionType : uint8
{
    UNKNOWN     UMETA(DisplayName = "Unknown"),
    PAID        UMETA(DisplayName = "Paid"),
    REDEEM      UMETA(DisplayName = "Redeem"),
    FREETRIAL   UMETA(DisplayName = "FreeTrial")
};

UCLASS()
class VIVEPORTSDK_API UViveportSubscription : public UObject
{
    GENERATED_BODY()

public:
    static void IsReady(ViveportApiStatus2* callback);
    static bool IsWindowsSubscriber();
    static bool IsAndroidSubscriber();
    static SubscriptionTransactionType GetTransactionType();
};
