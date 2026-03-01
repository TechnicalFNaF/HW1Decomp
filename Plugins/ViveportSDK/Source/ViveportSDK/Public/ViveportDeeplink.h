// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreUObject.h"
#include "ViveportType.h"
#include "ViveportDeeplink.generated.h"

/**
 * 
 */
UCLASS()
class VIVEPORTSDK_API UViveportDeeplink : public UObject
{
	GENERATED_BODY()
	
public:
    static void IsReady(ViveportApiStatus* callback);
    static void GoToApp(ViveportApiStatus2* callback, const FString viveportId, const FString launchData);
    static void GoToApp(ViveportApiStatus2* callback, const FString viveportId, const FString launchData, const FString branchName);
    static void GoToStore(ViveportApiStatus2* callback, const FString viveportId = TEXT(""));
    static void GoToAppOrGoToStore(ViveportApiStatus2* callback, const FString viveportId, const FString launchData);
    static FString GetAppLaunchData();
};

