// Fill out your copyright notice in the Description page of Project Settings.

#include "ViveportTokenDemo.h"
#include "ViveportSDKPrivatePCH.h"

UViveportTokenDemo::MyIsTokenReadyCallback myIsTokenReadyCallback;
UViveportTokenDemo::MyGetSessionTokenCallback myGetSessionTokenCallback;

// Sets default values for this component's properties
UViveportTokenDemo::UViveportTokenDemo()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UViveportTokenDemo::BeginPlay()
{
    Super::BeginPlay();

    UViveportApi::Init(&myInitCallback, APP_ID);
}

void UViveportTokenDemo::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    UViveportApi::Shutdown(&myShutdownCallback);
}

void UViveportTokenDemo::MyInitCallback::OnSuccess()
{
    FString fstring("Init success.");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    UViveportToken::IsReady(&myIsTokenReadyCallback);
}

void UViveportTokenDemo::MyInitCallback::OnFailure(int error_code)
{
    FString fstring = FString::Printf(TEXT("Init failure. error=%d"), error_code);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UViveportTokenDemo::MyIsTokenReadyCallback::OnSuccess()
{
    FString fstring("IsTokenReady success.");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    UViveportToken::GetSessionToken(&myGetSessionTokenCallback);
}

void UViveportTokenDemo::MyIsTokenReadyCallback::OnFailure(int error_code)
{
    FString fstring = FString::Printf(TEXT("IsTokenReady failure. error=%d"), error_code);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UViveportTokenDemo::MyGetSessionTokenCallback::OnSuccess(
    const FString& token
    )
{
    FString fstring = FString::Printf(TEXT("Session Token=%s"), *token);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UViveportTokenDemo::MyGetSessionTokenCallback::OnFailure(int error_code, const FString& error_message) {
    FString fstring = FString::Printf(TEXT("Get session token failed! error_code=%d"),
        error_code);
    if (!error_message.IsEmpty())
    {
        fstring += FString::Printf(TEXT(",\n error_message=%s"),
            *error_message);
    }
    
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UViveportTokenDemo::MyShutdownCallback::OnSuccess()
{
    FString fstring("Shutdown success.");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UViveportTokenDemo::MyShutdownCallback::OnFailure(int error_code)
{
    FString fstring = FString::Printf(TEXT("Shutdown failure. error=%d"), error_code);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}
