// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "ViveportApi.h"
#include "ViveportDLC.h"

#include "ViveportDLCDemo.generated.h"


UCLASS( ClassGroup=(Viveport), meta=(BlueprintSpawnableComponent) )
class VIVEPORTSDK_API UViveportDLCDemo : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UViveportDLCDemo();

    // Called when the game starts
    virtual void BeginPlay() override;

    void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    // Called every frame
    virtual void TickComponent(
        float DeltaTime,
        ELevelTick TickType,
        FActorComponentTickFunction* ThisTickFunction
    ) override;

    /** The APP ID for auth verify */
    FString DLC_APP_ID = "76d0898e-8772-49a9-aa55-1ec251a21686";

private:
    // callback interface
    class MyViveportDLCStatus : public ViveportApiStatus
    {
    protected:
        UViveportDLCDemo* mDemo;
    public:
        void SetDemoPtr(UViveportDLCDemo* p) { mDemo = p; }
    };

    class MyDLCInitCallback : public MyViveportDLCStatus
    {
    public:
        void OnSuccess(
        ) override;
        void OnFailure(int error_code
        ) override;
    };

    MyDLCInitCallback myDLCInitCallback;

    class MyDLCShutdownCallback : public MyViveportDLCStatus
    {
    public:
        void OnSuccess(
        ) override;
        void OnFailure(int error_code
        ) override;
    };

    MyDLCShutdownCallback myDLCShutdownCallback;

    class MyIsDLCReadyCallback : public MyViveportDLCStatus
    {
    public:
        void OnSuccess(
        ) override;
        void OnFailure(int error_code
        ) override;
    };

    MyIsDLCReadyCallback myIsDLCReadyCallback;

public:
    ViveportApiStatus* GetDLCInitCallback() { return &myDLCInitCallback; }
    ViveportApiStatus* GetDLCShutdownCallback() { return &myDLCShutdownCallback; }
    ViveportApiStatus* GetISDLCReadyCallback() { return &myIsDLCReadyCallback; }
};
