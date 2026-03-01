// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "ViveportApi.h"
#include "ViveportToken.h"

#include "ViveportTokenDemo.generated.h"

UCLASS(ClassGroup=(Viveport), meta=(BlueprintSpawnableComponent))
class VIVEPORTSDK_API UViveportTokenDemo : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UViveportTokenDemo();

    // Called when the game starts
    void BeginPlay() override;

    void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    FString APP_ID = "bd67b286-aafc-449d-8896-bb7e9b351876";

    class MyIsTokenReadyCallback : public ViveportApiStatus
    {
    public:
        void OnSuccess(
            ) override;
        void OnFailure(int error_code
            ) override;
    };

    class MyGetSessionTokenCallback : public ViveportApiStatus2
    {
    public:
        void OnSuccess(
            const FString& token
            ) override;
        void OnFailure(
            int errorCode,
            const FString& errorMessage
            ) override;
    };

private:
    // callback interface
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
