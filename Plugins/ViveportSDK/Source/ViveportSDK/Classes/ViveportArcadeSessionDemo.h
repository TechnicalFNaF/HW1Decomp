#pragma once

#include "Components/ActorComponent.h"
#include "ViveportType.h"
#include "ViveportArcadeSessionType.h"

#include "ViveportArcadeSessionDemo.generated.h"

UCLASS(ClassGroup = (Viveport), meta = (BlueprintSpawnableComponent))
class VIVEPORTSDK_API UViveportArcadeSessionDemo : public UActorComponent
{
    GENERATED_BODY()
public:
    // Called when the game starts
    void BeginPlay() override;

    void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    /** The APP ID for Session testing*/
    FString APP_ID = "3986c32c-64d4-4c5f-ab39-39afeb3fb6bf";
private:
    /** Callback objects */
    class MyViveportApiStatus : public ViveportApiStatus
    {
    protected:
        UViveportArcadeSessionDemo* mDemo;
    public:
        void SetDemoPtr(UViveportArcadeSessionDemo* p) { mDemo = p; }
    };

    class MyViveportArcadeSessionListener : public SessionListener
    {
    protected:
        UViveportArcadeSessionDemo* mDemo;
    public:
        void SetDemoPtr(UViveportArcadeSessionDemo* p) { mDemo = p; }
    };

    class MyInitCallback : public MyViveportApiStatus
    {
    public:
        void OnSuccess(
            ) override;
        void OnFailure(
            int nErrorCode
            ) override;
    };

    MyInitCallback myInitCallback;

    class MyShutdownCallback : public MyViveportApiStatus
    {
    public:
        void OnSuccess(
            ) override;
        void OnFailure(
            int nErrorCode
            ) override;
    };

    MyShutdownCallback myShutdownCallback;

    class MyIsReadyCallback : public MyViveportArcadeSessionListener
    {
    public:
        void OnSuccess(
            const FString& pchAppID
            ) override;
        void OnFailure(
            int nCode,
            const FString& pchMessage
            ) override;
    };

    MyIsReadyCallback myIsReadyCallback;

    class MyStartSessionCallback : public MyViveportArcadeSessionListener
    {
    public:
        void OnStartSuccess(
            const FString& pchAppID,
            const FString& pchGuid
            ) override;
        void OnFailure(
            int nCode,
            const FString& pchMessage
            ) override;
    };

    MyStartSessionCallback myStartSessionCallback;

    class MyStopSessionCallback : public MyViveportArcadeSessionListener
    {
    public:
        void OnStopSuccess(
            const FString& pchAppID,
            const FString& pchGuid
            ) override;
        void OnFailure(
            int nCode,
            const FString& pchMessage
            ) override;
    };

    MyStopSessionCallback myStopSessionCallback;
public:
    ViveportApiStatus* GetInitCallback() { return &myInitCallback; }
    ViveportApiStatus* GetShutdownCallback() { return &myShutdownCallback; }
    SessionListener* GetIsReadyCallback() { return &myIsReadyCallback; }
    SessionListener* GetStartSessionCallback() { return &myStartSessionCallback; }
    SessionListener* GetStopSessionCallback() { return &myStopSessionCallback; }
};