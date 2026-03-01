#pragma once

#include "Components/ActorComponent.h"
#include "ViveportApi.h"
#include "ViveportUser.h"
#include "ViveportType.h"
#include "ViveportUserStats.h"

#include "ViveportUserDemo.generated.h"

UCLASS(ClassGroup = (Viveport), meta = (BlueprintSpawnableComponent))
class VIVEPORTSDK_API UViveportUserDemo : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UViveportUserDemo();

    // Called when the game starts
    void BeginPlay() override;

    // Called every frame
    void TickComponent(
        float DeltaTime,
        ELevelTick TickType,
        FActorComponentTickFunction* ThisTickFunction
        ) override;

    /** The APP ID for auth verify */
    FString APP_ID = "bd67b286-aafc-449d-8896-bb7e9b351876";

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
};
