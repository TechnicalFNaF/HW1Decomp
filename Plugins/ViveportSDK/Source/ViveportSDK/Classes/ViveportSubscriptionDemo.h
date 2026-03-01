// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "ViveportApi.h"
#include "ViveportSubscription.h"

#include "ViveportSubscriptionDemo.generated.h"


UCLASS( ClassGroup=(Viveport), meta=(BlueprintSpawnableComponent) )
class VIVEPORTSDK_API UViveportSubscriptionDemo : public UActorComponent
{
    GENERATED_BODY()

public:
    // Called when the game starts
    virtual void BeginPlay() override;

    void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
   
    /** The APP ID for auth verify */
    FString APP_ID = "76d0898e-8772-49a9-aa55-1ec251a21686";

    class MyIsReadyCallback : public ViveportApiStatus2
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

private:
    // callback interface
    class MyViveportSubscriptionStatus : public ViveportApiStatus
    {
    protected:
        UViveportSubscriptionDemo* mDemo;
    public:
        void SetDemoPtr(UViveportSubscriptionDemo* p) { mDemo = p; }
    };

    class MySubscriptionInitCallback : public MyViveportSubscriptionStatus
    {
    public:
        void OnSuccess(
        ) override;
        void OnFailure(int error_code
        ) override;
    };

    MySubscriptionInitCallback mySubscriptionInitCallback;

    class MySubscriptionShutdownCallback : public MyViveportSubscriptionStatus
    {
    public:
        void OnSuccess(
        ) override;
        void OnFailure(int error_code
        ) override;
    };

    MySubscriptionShutdownCallback mySubscriptionShutdownCallback;

};
