// Some copyright should be here...

#pragma once

typedef void(*ViveportSDKStatusCallback)(int nResult);

class ViveportApiStatus
{
public:
    virtual ~ViveportApiStatus() { }
    virtual void OnSuccess() = 0;
    virtual void OnFailure(int nError) = 0;

protected:
    ViveportApiStatus() { }
};

class ViveportApiStatus2
{
public:
    virtual ~ViveportApiStatus2() { }
    virtual void OnSuccess(const FString& message) = 0;
    virtual void OnFailure(int nError, const FString& message) = 0;

protected:
    ViveportApiStatus2() { }
};

enum UELeaderboardDataDownload
{
    u_ELeaderboardDataDownloadGlobal = 0,
    u_ELeaderboardDataDownloadGlobalAroundUser = 1,
    u_ELeaderboardDataDownloadLocal = 2,
    u_ELeaderboardDataDownloadLocaleAroundUser = 3
};

enum UELeaderboardDataTimeRange
{
    u_ELeaderboardDataScropeAllTime = 0,
    u_ELeaderboardDataScropeDaily = 1,
    u_ELeaderboardDataScropeWeekly = 2,
    u_ELeaderboardDataScropeMonthly = 3
};

enum UELeaderboardSortMethod
{
    u_ELeaderboardSortMethodNone = 0,
    u_ELeaderboardSortMethodAscending = 1,
    u_ELeaderboardSortMethodDescending = 2
};

enum UELeaderboardDisplayType
{
    u_ELeaderboardDisplayTypeNone = 0,
    u_ELeaderboardDisplayTypeNumeric = 1,           // simple numerical score
    u_ELeaderboardDisplayTypeTimeSeconds = 2,       // the score represents a time, in seconds
    u_ELeaderboardDisplayTypeTimeMilliSeconds = 3   // the score represents a time, in milliseconds
};

enum UELeaderboardUploadScoreMethod
{
    u_ELeaderboardUploadScoreMethodNone = 0,
    u_ELeaderboardUploadScoreMethodKeepBest = 1,    // Leaderboard will keep user's best score
    u_ELeaderboardUploadScoreMethodForceUpdate = 2  // Leaderboard will always replace score with specified
};

struct ULeaderboardScore
{
    int Rank;           // [1..N], where N is the number of users with an entry in the leaderboard
    int Score;          // score as set in the leaderboard
    FString UserName;   // the user name showing in the leaderboard
};

