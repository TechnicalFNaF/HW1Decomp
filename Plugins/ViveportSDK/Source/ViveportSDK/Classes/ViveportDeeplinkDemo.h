
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "ViveportApi.h"
#include "ViveportDeeplink.h"
#include "ViveportDeeplinkDemo.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VIVEPORTSDK_API UViveportDeeplinkDemo : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UViveportDeeplinkDemo();

    /** The VIVEPORT ID for auth verify */
    FString VIVEPORT_ID = "bd67b286-aafc-449d-8896-bb7e9b351876";

    /** Public key for auth verify */
    FString VIVEPORT_KEY = "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDFypCg0OHfBC+VZLSWPbNSgDo9qg/yQORDwGy1rKIboMj3IXn4Zy6h6bgn8kiMY7VI0lPwIj9lijT3ZxkzuTsI5GsK//Y1bqeTol4OUFR+47gj+TUuekAS2WMtglKox+/7mO6CA1gV+jZrAKo6YSVmPd+oFsgisRcqEgNh5MIURQIDAQAB";

    FString TARGET_APP_VIVEPORT_ID = "bbbc73fc-b018-42ce-a049-439ab378dbc6";

    FString LAUNCH_DATA = "lauch_data";

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:	
    // callback interface
    class MyViveportDeeplinkStatus : public ViveportApiStatus
    {
    protected:
        UViveportDeeplinkDemo* mDemo;
    public:
        void SetDemoPtr(UViveportDeeplinkDemo* p) { mDemo = p; }
    };

    class MyViveportDeeplinkStatus2 : public ViveportApiStatus2
    {
    protected:
        UViveportDeeplinkDemo* mDemo;
    public:
        void SetDemoPtr(UViveportDeeplinkDemo* p) { mDemo = p; }
    };


    class MyInitCallback : public MyViveportDeeplinkStatus
    {
    public:
        void OnSuccess(
        ) override;
        void OnFailure(int errorCode
        ) override;
    };

    MyInitCallback myInitCallback;

    class MyDeeplinkIsReadyCallback : public MyViveportDeeplinkStatus
    {
    public:
        void OnSuccess(
        ) override;
        void OnFailure(int errorCode
        ) override;
    };

    MyDeeplinkIsReadyCallback myDeeplinkIsReadyCallback;

    class MyDeeplinkCallback : public MyViveportDeeplinkStatus2
    {
    public:
        void OnSuccess(
            const FString& result
        ) override;
        void OnFailure(
            int errorCode,
            const FString& errorMessage
        ) override;
    };

    MyDeeplinkCallback myDeeplinkCallback;

    MyDeeplinkIsReadyCallback* GetDeeplinkIsReadyCallback() { return &myDeeplinkIsReadyCallback; }
    MyDeeplinkCallback* GetDeeplinkCallback() { return &myDeeplinkCallback; }
};
