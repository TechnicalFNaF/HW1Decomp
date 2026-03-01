// Fill out your copyright notice in the Description page of Project Settings.

#include "ViveportDLCDemo.h"
#include "ViveportSDKPrivatePCH.h"


// Sets default values for this component's properties
UViveportDLCDemo::UViveportDLCDemo()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UViveportDLCDemo::BeginPlay()
{
    Super::BeginPlay();
    myDLCInitCallback.SetDemoPtr(this);
    myIsDLCReadyCallback.SetDemoPtr(this);

    UViveportApi::Init(&myDLCInitCallback, DLC_APP_ID);
}

void UViveportDLCDemo::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    // Call ViveportApi::Shutdown()
    UViveportApi::Shutdown(&myDLCShutdownCallback);
}


// Called every frame
void UViveportDLCDemo::TickComponent(
    float DeltaTime,
    ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction
    )
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

/***************************************************************
*					MyDLCInitCallback
***************************************************************/

void UViveportDLCDemo::MyDLCInitCallback::OnSuccess()
{
    FString fstring("Init success.");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    UViveportDLC::IsReady(mDemo->GetISDLCReadyCallback());
}

void UViveportDLCDemo::MyDLCInitCallback::OnFailure(int error_code)
{
    FString fstring = FString::Printf(TEXT("Init failure. error=%d"), error_code);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

/***************************************************************
*					MyDLCShutdownCallback
***************************************************************/

void UViveportDLCDemo::MyDLCShutdownCallback::OnSuccess()
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportDLCDemo][MyDLCShutdownCallback] Shutdown success."));
    FString fstring("Shutdown success.");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UViveportDLCDemo::MyDLCShutdownCallback::OnFailure(int error_code)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportDLCDemo][MyDLCShutdownCallback] Shutdown failure. Error = %d"), error_code);
    FString fstring = FString::Printf(TEXT("Shutdown failure. error=%d"), error_code);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

/***************************************************************
*					MyISDLCReadyCallback
***************************************************************/

void UViveportDLCDemo::MyIsDLCReadyCallback::OnSuccess()
{
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportDLCDemo][MyIsDLCReadyCallback] IsReady success."));
    FString fstring = FString::Printf(TEXT("Is ready success"));
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    // Get DLC count
    int dlcCount = UViveportDLC::GetCount();
    UE_LOG(ViveportSDK, Log, TEXT("[UViveportDLCDemo][GetDLCCount] %d"), dlcCount);
    fstring = FString::Printf(TEXT("GetDLCCount: %d"), dlcCount);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    // Get DLC data by index
    static FString dlcAppId = mDemo->DLC_APP_ID;
    static bool isAvailable = false;
    bool isIndexZeroInRange = UViveportDLC::GetIsAvailable(0, dlcAppId, isAvailable);
    if (isIndexZeroInRange)
    {
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportDLCDemo][GetDLCDataByIndex] DLC App ID: %s, Is available: %s"),
            *dlcAppId,
            isAvailable ? TEXT("true") : TEXT("false"));
        fstring = FString::Printf(TEXT("DLC App ID: %s, Is available: %s"),
            *dlcAppId,
            isAvailable ? TEXT("true") : TEXT("false"));
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
    }
    else
    {
        UE_LOG(ViveportSDK, Log, TEXT("[UViveportDLCDemo][GetDLCDataByIndex] Index zero is not in range"));
        fstring = FString::Printf(TEXT("Index zero is not in range"));
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
    }
}

void UViveportDLCDemo::MyIsDLCReadyCallback::OnFailure(int error_code)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportDLCDemo][MyIsDLCReadyCallback] IsReady failure. Code = %d"), error_code);
    FString fstring = FString::Printf(TEXT("IsReady failure. Code = %d"), error_code);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}
