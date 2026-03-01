// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "ViveportApi.h"

#include "ViveportApiDemo.generated.h"


UCLASS( ClassGroup=(Viveport), meta=(BlueprintSpawnableComponent) )
class VIVEPORTSDK_API UViveportApiDemo : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UViveportApiDemo();

    // Called when the game starts
    void BeginPlay() override;

    void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    // Called every frame
    void TickComponent(
            float DeltaTime,
            ELevelTick TickType,
            FActorComponentTickFunction* ThisTickFunction
    ) override;

    /** The APP ID for auth verify */
    FString APP_ID = "bd67b286-aafc-449d-8896-bb7e9b351876";

    /** Public key for auth verify */
    FString APP_KEY = "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDFypCg0OHfBC+VZLSWPbNSgDo9qg/yQORDwGy1rKIboMj3IXn4Zy6h6bgn8kiMY7VI0lPwIj9lijT3ZxkzuTsI5GsK//Y1bqeTol4OUFR+47gj+TUuekAS2WMtglKox+/7mO6CA1gV+jZrAKo6YSVmPd+oFsgisRcqEgNh5MIURQIDAQAB";

private:
    // callback interface
    class MyLicenseChecker : public UViveportApi::LicenseChecker
    {
    public:
        void OnSuccess(
                long long issue_time,
                long long expiration_time,
                int latest_version,
                bool update_required
        ) override;
        void OnFailure(
                int errorCode,
                const FString& errorMessage
        ) override;
    };

    MyLicenseChecker myLicenseChecker;

    class MyInitCallback : public ViveportApiStatus
    {
    public:
        void OnSuccess(
            ) override;
        void OnFailure(int error_code
            ) override;
    };

    MyInitCallback myInitCallback;

    class MyShutdownCallback : public ViveportApiStatus
    {
    public:
        void OnSuccess(
            ) override;
        void OnFailure(int error_code
            ) override;
    };

    MyShutdownCallback myShutdownCallback;
};
