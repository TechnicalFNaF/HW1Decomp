// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreUObject.h"
#include "ViveportType.h"

#include "ViveportUserStats.generated.h"

/**
*
*/
UCLASS()
class VIVEPORTSDK_API UViveportUserStats : public UObject
{
    GENERATED_BODY()

public:
    static bool IsReady(ViveportApiStatus *);
    static int DownloadStats(ViveportApiStatus *);
    static int UploadStats(ViveportApiStatus *);

    /********************************************************/
    /*                Stats functions                       */
    /********************************************************/
    // Data accessors
    static int GetStat(const FString, int);
    static float GetStat(const FString, float);
    static int SetStat(const FString, int);
    static int SetStat(const FString, float);

    /*********************************************************/
    /*                Achievement functions                  */
    /*********************************************************/
    static bool GetAchievement(const FString);
    static int GetAchievementUnlockTime(const FString);
    static int SetAchievement(const FString);
    static int ClearAchievement(const FString);

    /*********************************************************/
    /*                Leaderboard functions                  */
    /*********************************************************/
    static int DownloadLeaderboardScores(ViveportApiStatus *,
                                const FString fLeaderboardName,
                                UELeaderboardDataDownload eLeaderboardDataDownload,
                                UELeaderboardDataTimeRange eLeaderboardDataTimeRange,
                                int nRangeStart,
                                int nRangeEnd);
    static int UploadLeaderboardScore(ViveportApiStatus *, const FString, int nScore);
    static ULeaderboardScore GetLeaderboardScore(int index);
    static int GetLeaderboardScoreCount();
    static UELeaderboardSortMethod GetLeaderboardSortMethod();
    static UELeaderboardDisplayType GetLeaderboardDisplayType();
};