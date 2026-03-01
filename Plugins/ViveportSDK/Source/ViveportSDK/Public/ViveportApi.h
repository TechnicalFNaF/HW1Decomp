// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreUObject.h"
#include "ViveportType.h"

#include "ViveportApi.generated.h"


/**
 * 
 */
UCLASS()
class VIVEPORTSDK_API UViveportApi : public UObject
{
    GENERATED_BODY()

public:
    class LicenseChecker;

    static int Init(
            ViveportApiStatus *callback,
            const FString app_id
    );
    static void GetLicense(
            LicenseChecker *license_checker,
            const FString app_id,
            const FString app_key
    );
    static int Shutdown(ViveportApiStatus *callback);
    static FString Version();
};

class UViveportApi::LicenseChecker
{
public:
    virtual ~LicenseChecker() { }
    virtual void OnSuccess(
            long long issue_time,
            long long expiration_time,
            int latest_version,
            bool update_required
    ) = 0;
    virtual void OnFailure(
            int errorCode,
            const FString& error_message
    ) = 0;

protected:
    LicenseChecker() { }
};
