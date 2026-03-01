// Fill out your copyright notice in the Description page of Project Settings.

#include "ViveportUserStatsDemo.h"
#include "ViveportSDKPrivatePCH.h"

UViveportUserStatsDemo::MyInitCallback myInitCallback;
UViveportUserStatsDemo::MyShutdownCallback myShutdownCallback;
UViveportUserStatsDemo::MyIsReadyStatus myIsReadyStatus;
UViveportUserStatsDemo::MyDownloadStatsStatus myDownloadStatsStatus;
UViveportUserStatsDemo::MyUploadStatsStatus myUploadStatsStatus;
UViveportUserStatsDemo::MyDownloadLeaderboardScoreStatus myDownloadLeaderboardScoreStatus;
UViveportUserStatsDemo::MyUploadLeaderboardScoreStatus myUploadLeaderboardScoreStatus;

//Leaderboard information
FString fLeaderBoardName = "ID_Leaderboard1";
int upload_score = 10;
//Download Leaderboard conditions
UELeaderboardDataDownload leaderboard_scope = u_ELeaderboardDataDownloadLocal;
UELeaderboardDataTimeRange leaderboard_time_range = u_ELeaderboardDataScropeAllTime;
int range_start = 0;
int range_end = 10;

FString stat_key_1 = "ID_Stat1";
FString stat_key_2 = "ID_Stat2";
int stat_key_default_1 = 0;
float stat_key_default_2 = 0.0f;
FString achievement_name = "ID_Achievement1";

// Sets default values for this component's properties
UViveportUserStatsDemo::UViveportUserStatsDemo()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UViveportUserStatsDemo::BeginPlay()
{
    Super::BeginPlay();

    UViveportApi::Init(&myInitCallback, APP_ID);
}


void UViveportUserStatsDemo::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    UViveportApi::Shutdown(&myShutdownCallback);
}

// Called every frame
void UViveportUserStatsDemo::TickComponent(
    float DeltaTime,
    ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction
    )
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UViveportUserStatsDemo::MyInitCallback::OnSuccess()
{
    FString fstring("Init success.");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
    UViveportUserStats::IsReady(&myIsReadyStatus);
}

void UViveportUserStatsDemo::MyInitCallback::OnFailure(int error)
{
    char result[256] = { '\0' };
#if PLATFORM_WINDOWS
    sprintf_s(
#elif PLATFORM_ANDROID
    sprintf(
#endif
        result,
        "Init failure. error code=%d",
        error
        );
    FString fstring(result);

    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UViveportUserStatsDemo::MyIsReadyStatus::OnSuccess()
{
    FString fstring("IsReady success.");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    UViveportUserStats::DownloadStats(&myDownloadStatsStatus);
    UViveportUserStats::UploadLeaderboardScore(&myUploadLeaderboardScoreStatus, fLeaderBoardName, upload_score);
}

void UViveportUserStatsDemo::MyIsReadyStatus::OnFailure(int error)
{
    const FString fstring = FString::Printf(TEXT("IsReady failure. error=%d"), error);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UViveportUserStatsDemo::MyDownloadStatsStatus::OnSuccess()
{
    FString fstring("MyDownloadStatsStatus success.");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    int stat_1 = UViveportUserStats::GetStat(stat_key_1, stat_key_default_1);
    float stat_2 = UViveportUserStats::GetStat(stat_key_2, stat_key_default_2);

    fstring = FString::Printf(TEXT("getStats, %s=%d, %s=%f"), *stat_key_1, stat_1, *stat_key_2, stat_2);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    stat_1++; stat_2++;
    UViveportUserStats::SetStat(stat_key_1, stat_1);
    UViveportUserStats::SetStat(stat_key_2, stat_2);

    fstring = FString::Printf(TEXT("setStats, %s=%d, %s=%f"), *stat_key_1, stat_1, *stat_key_2, stat_2);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    bool achieved = UViveportUserStats::GetAchievement(achievement_name);
    fstring = FString::Printf(TEXT("GetAchievement, name=%s, achieved=%s"),
                            *achievement_name,
                            achieved ? *FString("true") : *FString("false"));
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    if (achieved)
        UViveportUserStats::ClearAchievement(achievement_name);
    else
        UViveportUserStats::SetAchievement(achievement_name);
    UViveportUserStats::UploadStats(&myUploadStatsStatus);
}

void UViveportUserStatsDemo::MyDownloadStatsStatus::OnFailure(int error)
{
    const FString fstring = FString::Printf(TEXT("DownloadStats failure. error=%d"), error);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UViveportUserStatsDemo::MyUploadStatsStatus::OnSuccess()
{
    FString fstring("UploadStats success.");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UViveportUserStatsDemo::MyUploadStatsStatus::OnFailure(int error)
{
    const FString fstring = FString::Printf(TEXT("UploadStats failure. error=%d"), error);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UViveportUserStatsDemo::MyDownloadLeaderboardScoreStatus::OnSuccess()
{
    FString fstring("DownloadLeaderboardScore success.");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    fstring = FString::Printf(TEXT("GetLeaderboardSortMethod=%d\nGetLeaderboardDisplayType=%d"),
                                (int) UViveportUserStats::GetLeaderboardSortMethod(),
                                (int) UViveportUserStats::GetLeaderboardDisplayType()
                             );
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    int size = UViveportUserStats::GetLeaderboardScoreCount();
    for (int i = 0; i < size; i++)
    {
        ULeaderboardScore leaderboardScore = UViveportUserStats::GetLeaderboardScore(i);
        fstring = FString::Printf(TEXT("rank=%d, name=%s, score=%d"),
                                        leaderboardScore.Rank,
                                        *leaderboardScore.UserName,
                                        leaderboardScore.Score);
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
    }

}

void UViveportUserStatsDemo::MyDownloadLeaderboardScoreStatus::OnFailure(int error)
{
    const FString fstring = FString::Printf(TEXT("DownloadLeaderboardScore failure. error=%d"), error);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UViveportUserStatsDemo::MyUploadLeaderboardScoreStatus::OnSuccess()
{
    FString fstring("UploadLeaderboardScore success.");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);

    UViveportUserStats::DownloadLeaderboardScores(&myDownloadLeaderboardScoreStatus,
                                                    fLeaderBoardName,
                                                    leaderboard_scope,
                                                    leaderboard_time_range,
                                                    range_start,
                                                    range_end
                                                );
}

void UViveportUserStatsDemo::MyUploadLeaderboardScoreStatus::OnFailure(int error)
{
    const FString fstring = FString::Printf(TEXT("UploadLeaderboardScore failure. error=%d"), error);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UViveportUserStatsDemo::MyShutdownCallback::OnSuccess()
{
    FString fstring("Shutdown success.");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

void UViveportUserStatsDemo::MyShutdownCallback::OnFailure(int error_code)
{
    FString fstring = FString::Printf(TEXT("Shutdown failure. error=%d"), error_code);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, fstring);
}

