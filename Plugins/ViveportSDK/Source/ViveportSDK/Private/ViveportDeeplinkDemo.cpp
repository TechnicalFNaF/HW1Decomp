// Fill out your copyright notice in the Description page of Project Settings.

#include "ViveportDeeplinkDemo.h"
#include "ViveportSDKPrivatePCH.h"

// Sets default values for this component's properties
UViveportDeeplinkDemo::UViveportDeeplinkDemo()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UViveportDeeplinkDemo::BeginPlay()
{
	Super::BeginPlay();

    myInitCallback.SetDemoPtr(this);
    myDeeplinkIsReadyCallback.SetDemoPtr(this);
    UViveportApi::Init(&myInitCallback, VIVEPORT_ID);
}

/***************************************************************
*					MyInitCallback
***************************************************************/

void UViveportDeeplinkDemo::MyInitCallback::OnSuccess()
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportDeeplinkDemo][MyInitCallback] Init Success"));
    FString fstring("Init success.");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
    UViveportDeeplink::IsReady(mDemo->GetDeeplinkIsReadyCallback());
}

void UViveportDeeplinkDemo::MyInitCallback::OnFailure(int errorCode)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportDeeplinkDemo][MyInitCallback] Init failure. Code = %d"), errorCode);
    FString fstring = FString::Printf(TEXT("Init failure. error=%d"), errorCode);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UViveportDeeplinkDemo::MyDeeplinkIsReadyCallback::OnSuccess()
{
    FString lauchData = TEXT("GetLaunchData : ") + UViveportDeeplink::GetAppLaunchData();
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, lauchData);
    
    FString f1string("Start GoToAppOrGoToStore");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, f1string);
    UViveportDeeplink::GoToAppOrGoToStore(mDemo->GetDeeplinkCallback(), mDemo->TARGET_APP_VIVEPORT_ID, mDemo->VIVEPORT_KEY);
    
    /* Test GoToApp
    FString fstring("Start GoToApp");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
    UViveportDeeplink::GoToApp(mDemo->GetDeeplinkCallback(), mDemo->TARGET_APP_VIVEPORT_ID, mDemo->VIVEPORT_KEY);
    */

    /*Test GoToApp with BranchName PROD or BETA
    FString f2string("Start GoToApp");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, f2string);
    UViveportDeeplink::GoToApp(mDemo->GetDeeplinkCallback(), mDemo->TARGET_APP_VIVEPORT_ID, mDemo->VIVEPORT_KEY, TEXT("PROD"));
    */

    /*Test GoToStore
    FString f3String("Start GoToStore");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, f3String);
    UViveportDeeplink::GoToStore(mDemo->GetDeeplinkCallback(), mDemo->TARGET_APP_VIVEPORT_ID);
    */
}

void UViveportDeeplinkDemo::MyDeeplinkIsReadyCallback::OnFailure(int errorCode)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportDeeplinkDemo][MyDeeplinkIsReadyCallback] DeeplinkIsReady failure. Code = %d"), errorCode);
    FString fstring = FString::Printf(TEXT("DeeplinkIsReady failure. error=%d"), errorCode);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

/***************************************************************
*					MyDeeplinkCallback
***************************************************************/

void UViveportDeeplinkDemo::MyDeeplinkCallback::OnSuccess(const FString& result)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportDeeplinkDemo][MyDeeplinkCallback] DeeplinkCallback Success"));
    FString fstring("Deeplink is Success!!");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UViveportDeeplinkDemo::MyDeeplinkCallback::OnFailure(int errorCode, const FString& errorMessage)
{
    UE_LOG(ViveportSDK, Error, TEXT("[UViveportDeeplinkDemo][MyDeeplinkCallback] DeeplinkCallback failure. Code = %d"), errorCode);
    FString fstring = FString::Printf(TEXT("DeeplinkCallback failure errorCode = %d errorMessage = %s"), errorCode, *errorMessage);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}


