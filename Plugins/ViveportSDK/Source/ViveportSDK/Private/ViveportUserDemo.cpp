// Fill out your copyright notice in the Description page of Project Settings.

#include "ViveportUserDemo.h"
#include "ViveportSDKPrivatePCH.h"

UViveportUserDemo::MyInitCallback initCallback;
UViveportUserDemo::MyIsReadyStatus isReadyStatus;

// Sets default values for this component's properties
UViveportUserDemo::UViveportUserDemo()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UViveportUserDemo::BeginPlay()
{
    Super::BeginPlay();

    UViveportApi::Init(&initCallback, APP_ID);
}

void UViveportUserDemo::MyInitCallback::OnSuccess()
{
    FString fstring("Init success.");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
    UViveportUser::IsReady(&isReadyStatus);
}

void UViveportUserDemo::MyInitCallback::OnFailure(int error)
{
    char result[256] = { '\0' };
#if PLATFORM_WINDOWS
    sprintf_s(
#elif PLATFORM_ANDROID
    sprintf(
#endif
        result,
        "Init failure. error code=%d",
        error
    );
    FString fstring(result);

    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UViveportUserDemo::MyIsReadyStatus::OnSuccess()
{
    FString fstring("IsReady success.");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

        fstring = FString::Printf(TEXT("GetUserID=%s\nGetUserName=%s\nGetUserAvatarUrl=%s"),
            *UViveportUser::GetUserID(),
            *UViveportUser::GetUserName(),
            *UViveportUser::GetUserAvatarUrl());
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UViveportUserDemo::MyIsReadyStatus::OnFailure(int error)
{
    const FString fstring = FString::Printf(TEXT("IsReady failure. error=%d"), error);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

// Called every frame
void UViveportUserDemo::TickComponent(
    float DeltaTime,
    ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction
    )
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}