#pragma once

#include "Components/ActorComponent.h"
#include "ViveportApi.h"
#include "ViveportUserStats.h"
#include "ViveportType.h"

#include "ViveportUserStatsDemo.generated.h"

UCLASS(ClassGroup = (Viveport), meta = (BlueprintSpawnableComponent))
class VIVEPORTSDK_API UViveportUserStatsDemo : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UViveportUserStatsDemo();

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

public:

    class MyInitCallback : public ViveportApiStatus
    {
    public:
        void OnSuccess(
            ) override;
        void OnFailure(int errorCode
            ) override;
    };

    class MyIsReadyStatus : public ViveportApiStatus
    {
    public:
        void OnSuccess(
            ) override;
        void OnFailure(int errorCode
            ) override;
    };

    class MyDownloadStatsStatus : public ViveportApiStatus
    {
    public:
        void OnSuccess(
            ) override;
        void OnFailure(int errorCode
            ) override;
    };

    class MyUploadStatsStatus : public ViveportApiStatus
    {
    public:
        void OnSuccess(
            ) override;
        void OnFailure(int errorCode
            ) override;
    };

    class MyDownloadLeaderboardScoreStatus : public ViveportApiStatus
    {
    public:
        void OnSuccess(
            ) override;
        void OnFailure(int errorCode
            ) override;
    }; 

    class MyUploadLeaderboardScoreStatus : public ViveportApiStatus
    {
    public:
        void OnSuccess(
            ) override;
        void OnFailure(int errorCode
            ) override;
    };

    class MyShutdownCallback : public ViveportApiStatus
    {
    public:
        void OnSuccess(
            ) override;
        void OnFailure(int error_code
            ) override;
    };
};
