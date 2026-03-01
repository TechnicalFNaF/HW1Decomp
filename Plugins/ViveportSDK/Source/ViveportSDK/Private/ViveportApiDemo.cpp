// Fill out your copyright notice in the Description page of Project Settings.

#include "ViveportApiDemo.h"
#include "ViveportSDKPrivatePCH.h"


// Sets default values for this component's properties
UViveportApiDemo::UViveportApiDemo()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UViveportApiDemo::BeginPlay()
{
    Super::BeginPlay();
    FString fstring = UViveportApi::Version();
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    // ...
    UViveportApi::GetLicense(&myLicenseChecker, APP_ID, APP_KEY);
    UViveportApi::Init(&myInitCallback, APP_ID);
}

void UViveportApiDemo::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    UViveportApi::Shutdown(&myShutdownCallback);
}

// Called every frame
void UViveportApiDemo::TickComponent(
    float DeltaTime,
    ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction
    )
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UViveportApiDemo::MyLicenseChecker::OnSuccess(
    long long issue_time,
    long long expiration_time,
    int latest_version,
    bool update_required
    )
{
    FString fstring = FString::Printf(TEXT("Verify OK!\n issue_time=%lld,\n expiration_time=%lld,\n latest_version=%d,\n update_required=%d"),
        issue_time,
        expiration_time,
        latest_version,
        update_required);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UViveportApiDemo::MyLicenseChecker::OnFailure(int error_code, const FString& error_message) {
    FString fstring = FString::Printf(TEXT("Verify failed!\n error_code=%d,\n error_message=%s"),
        error_code,
        *error_message);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UViveportApiDemo::MyInitCallback::OnSuccess()
{
    FString fstring("Init success.");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UViveportApiDemo::MyInitCallback::OnFailure(int error_code)
{
    FString fstring = FString::Printf(TEXT("Init failure. error=%d"), error_code);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UViveportApiDemo::MyShutdownCallback::OnSuccess()
{
    FString fstring("Shutdown success.");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UViveportApiDemo::MyShutdownCallback::OnFailure(int error_code)
{
    FString fstring = FString::Printf(TEXT("Shutdown failure. error=%d"), error_code);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}
