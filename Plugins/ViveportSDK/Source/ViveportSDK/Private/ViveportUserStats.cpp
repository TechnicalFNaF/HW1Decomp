// Fill out your copyright notice in the Description page of Project Settings.

#include "ViveportUserStats.h"
#include "ViveportSDKPrivatePCH.h"
#include <string>

#include "viveport_api.h"

static ViveportApiStatus* is_ready_status;
static ViveportApiStatus* download_stats_status;
static ViveportApiStatus* upload_stats_status;
static ViveportApiStatus* upload_leaderboard_status;
static ViveportApiStatus* download_leaderboard_status;

void IsReadyHandler(int);
void DownloadStatsHandler(int);
void UploadStatsHandler(int);
void DownloadLeaderboardScoreHandler(int);
void UploadLeaderboardScoreHandler(int);

bool UViveportUserStats::IsReady(ViveportApiStatus *callback)
{
#if PLATFORM_WINDOWS
    int ret = 0;
    if (FViveportSDKModule::IsAvailable())
    {
        is_ready_status = callback;
        ret = ViveportUserStats()->IsReady(IsReadyHandler);
    }
    return ret == 1;
#elif PLATFORM_ANDROID
    static ViveportApiStatus* cb = callback;
    ViveportCallback::OnResult onResult =
        [](int code, std::string message)
    {
        int64 statusCode = -1;
        FString currencyName;
        FString errMessage;

        if (code == 0)
        {
            TSharedPtr<FJsonObject> json_object;
            auto json_reader = TJsonReaderFactory<TCHAR>::Create(UTF8_TO_TCHAR(message.c_str()));
            if (FJsonSerializer::Deserialize(json_reader, json_object))
            {
                FString statusCodeStr = json_object->GetStringField("statusCode");
                statusCode = FCString::Atoi64(*statusCodeStr);
                errMessage = json_object->GetStringField("message");
            }
        }

        if (cb != nullptr)
        {
            if (code == 0)
            {
                if (statusCode == 0)
                    cb->OnSuccess();
                else
                    cb->OnFailure(statusCode);
            }
            else
                cb->OnFailure(code);
        }
    };

    return ((ViveportUserStats::IsReady(onResult) == 0) ? true : false);
#else
#endif
}

int UViveportUserStats::DownloadStats(ViveportApiStatus *callback)
{
#if PLATFORM_WINDOWS
    int ret = 0;
    if (FViveportSDKModule::IsAvailable())
    {
        download_stats_status = callback;
        ret = ViveportUserStats()->DownloadStats(DownloadStatsHandler);
    }
    return ret;
#elif PLATFORM_ANDROID
    static ViveportApiStatus* cb = callback;
    ViveportCallback::OnResult onResult =
        [](int code, std::string message)
    {
        int64 statusCode = -1;
        FString currencyName;
        FString errMessage;

        if (code == 0)
        {
            TSharedPtr<FJsonObject> json_object;
            auto json_reader = TJsonReaderFactory<TCHAR>::Create(UTF8_TO_TCHAR(message.c_str()));
            if (FJsonSerializer::Deserialize(json_reader, json_object))
            {
                FString statusCodeStr = json_object->GetStringField("statusCode");
                statusCode = FCString::Atoi64(*statusCodeStr);
                errMessage = json_object->GetStringField("message");
            }
        }

        if (cb != nullptr)
        {
            if (code == 0)
            {
                if (statusCode == 0)
                    cb->OnSuccess();
                else
                    cb->OnFailure(statusCode);
            }
            else
                cb->OnFailure(code);
        }
    };

    return ViveportUserStats::DownloadStats(onResult);
#else
#endif
}

int UViveportUserStats::UploadStats(ViveportApiStatus *callback)
{
#if PLATFORM_WINDOWS
    int ret = 0;
    if (FViveportSDKModule::IsAvailable())
    {
        upload_stats_status = callback;
        ret = ViveportUserStats()->UploadStats(UploadStatsHandler);
    }
    return ret;
#elif PLATFORM_ANDROID
    static ViveportApiStatus* cb = callback;
    ViveportCallback::OnResult onResult =
        [](int code, std::string message)
    {
        int64 statusCode = -1;
        FString currencyName;
        FString errMessage;

        if (code == 0)
        {
            TSharedPtr<FJsonObject> json_object;
            auto json_reader = TJsonReaderFactory<TCHAR>::Create(UTF8_TO_TCHAR(message.c_str()));
            if (FJsonSerializer::Deserialize(json_reader, json_object))
            {
                FString statusCodeStr = json_object->GetStringField("statusCode");
                statusCode = FCString::Atoi64(*statusCodeStr);
                errMessage = json_object->GetStringField("message");
            }
        }

        if (cb != nullptr)
        {
            if (code == 0)
            {
                if (statusCode == 0)
                    cb->OnSuccess();
                else
                    cb->OnFailure(statusCode);
            }
            else
                cb->OnFailure(code);
        }
    };

    return ViveportUserStats::UploadStats(onResult);
#else
#endif
}

int UViveportUserStats::GetStat(const FString fName, int default_value)
{
#if PLATFORM_WINDOWS
    int data = default_value;
    if (FViveportSDKModule::IsAvailable())
    {
        ViveportUserStats()->GetStat(TCHAR_TO_ANSI(*fName), &data);
    }
    return data;
#elif PLATFORM_ANDROID
    return ViveportUserStats::GetStats(std::string(TCHAR_TO_UTF8(*fName)), default_value);
#else
#endif
}

float UViveportUserStats::GetStat(const FString fName, float default_value)
{
#if PLATFORM_WINDOWS
    float data = default_value;
    if (FViveportSDKModule::IsAvailable())
    {
        ViveportUserStats()->GetStat(TCHAR_TO_ANSI(*fName), &data);
    }
    return data;
#elif PLATFORM_ANDROID
    return ViveportUserStats::GetStats(std::string(TCHAR_TO_UTF8(*fName)), default_value);
#else
#endif
}

int UViveportUserStats::SetStat(const FString fName, int data)
{
#if PLATFORM_WINDOWS
    int ret = 0;
    if (FViveportSDKModule::IsAvailable())
    {
        ret = ViveportUserStats()->SetStat(TCHAR_TO_ANSI(*fName), data);
    }
    return ret;
#elif PLATFORM_ANDROID
    return ViveportUserStats::SetStats(std::string(TCHAR_TO_UTF8(*fName)), data);
#else
#endif
}

int UViveportUserStats::SetStat(const FString fName, float fData)
{
#if PLATFORM_WINDOWS
    int ret = 0;
    if (FViveportSDKModule::IsAvailable())
    {
        ret = ViveportUserStats()->SetStat(TCHAR_TO_ANSI(*fName), fData);
    }
    return ret;
#elif PLATFORM_ANDROID
    return ViveportUserStats::SetStats(std::string(TCHAR_TO_UTF8(*fName)), fData);
#else
#endif
}

bool UViveportUserStats::GetAchievement(const FString fName)
{
#if PLATFORM_WINDOWS
    int achieved = 0;
    if (FViveportSDKModule::IsAvailable())
    {
        ViveportUserStats()->GetAchievement(TCHAR_TO_ANSI(*fName), &achieved);
    }
    return achieved == 1;
#elif PLATFORM_ANDROID
    return ViveportUserStats::GetAchievement(std::string(TCHAR_TO_UTF8(*fName)));
#else
#endif
}

int UViveportUserStats::GetAchievementUnlockTime(const FString fName)
{
#if PLATFORM_WINDOWS
    int unlockTime = 0;
    if (FViveportSDKModule::IsAvailable())
    {
        ViveportUserStats()->GetAchievementUnlockTime(TCHAR_TO_ANSI(*fName), &unlockTime);
    }
    return unlockTime;
#elif PLATFORM_ANDROID
    return ViveportUserStats::GetAchievementUnlockTime(std::string(TCHAR_TO_UTF8(*fName)));
#else
#endif
}

int UViveportUserStats::SetAchievement(const FString fName)
{
#if PLATFORM_WINDOWS
    int ret = 0;
    if (FViveportSDKModule::IsAvailable())
    {
        ret = ViveportUserStats()->SetAchievement(TCHAR_TO_ANSI(*fName));
    }
    return ret;
#elif PLATFORM_ANDROID
    return ViveportUserStats::SetAchievement(std::string(TCHAR_TO_UTF8(*fName)));
#else
#endif
}

int UViveportUserStats::ClearAchievement(const FString fName)
{
#if PLATFORM_WINDOWS
    int ret = 0;
    if (FViveportSDKModule::IsAvailable())
    {
        ret = ViveportUserStats()->ClearAchievement(TCHAR_TO_ANSI(*fName));
    }
    return ret;
#elif PLATFORM_ANDROID
    return ViveportUserStats::ClearAchievement(std::string(TCHAR_TO_UTF8(*fName)));
#else
#endif
}

int UViveportUserStats::DownloadLeaderboardScores(ViveportApiStatus *callback,
    const FString fLeaderboardName,
    UELeaderboardDataDownload eLeaderboardDataDownload,
    UELeaderboardDataTimeRange eLeaderboardDataTimeRange,
    int nRangeStart,
    int nRangeEnd)
{
#if PLATFORM_WINDOWS
    int ret = 0;
    if (FViveportSDKModule::IsAvailable())
    {
        download_leaderboard_status = callback;

        ret = ViveportUserStats()->DownloadLeaderboardScores(DownloadLeaderboardScoreHandler,
                                                            TCHAR_TO_ANSI(*fLeaderboardName),
                                                            (ELeaderboardDataDownload) eLeaderboardDataDownload,
                                                            (ELeaderboardDataTimeRange) eLeaderboardDataTimeRange,
                                                            nRangeStart,
                                                            nRangeEnd);
    }
    return ret;
#elif PLATFORM_ANDROID
    static ViveportApiStatus* cb = callback;
    ViveportCallback::OnResult onResult =
        [](int code, std::string message)
    {
        int64 statusCode = -1;
        FString currencyName;
        FString errMessage;

        if (code == 0)
        {
            TSharedPtr<FJsonObject> json_object;
            auto json_reader = TJsonReaderFactory<TCHAR>::Create(UTF8_TO_TCHAR(message.c_str()));
            if (FJsonSerializer::Deserialize(json_reader, json_object))
            {
                FString statusCodeStr = json_object->GetStringField("statusCode");
                statusCode = FCString::Atoi64(*statusCodeStr);
                errMessage = json_object->GetStringField("message");
            }
        }

        if (cb != nullptr)
        {
            if (code == 0)
            {
                if (statusCode == 0)
                    cb->OnSuccess();
                else
                    cb->OnFailure(statusCode);
            }
            else
                cb->OnFailure(code);
        }
    };

    return ViveportUserStats::GetLeaderboard(
        onResult,
        std::string(TCHAR_TO_UTF8(*fLeaderboardName)),
        nRangeStart,
        nRangeEnd,
        static_cast<int>(eLeaderboardDataTimeRange),
        static_cast<int>(eLeaderboardDataDownload));
#else
#endif
}

int UViveportUserStats::UploadLeaderboardScore(ViveportApiStatus *callback, const FString fName, int nScore)
{
#if PLATFORM_WINDOWS
    int ret = 0;
    if (FViveportSDKModule::IsAvailable())
    {
        upload_leaderboard_status = callback;
        ret = ViveportUserStats()->UploadLeaderboardScore(UploadLeaderboardScoreHandler,
                                                        TCHAR_TO_ANSI(*fName),
                                                        nScore);
    }
    return ret;
#elif PLATFORM_ANDROID
    static ViveportApiStatus* cb = callback;
    ViveportCallback::OnResult onResult =
        [](int code, std::string message)
    {
        int64 statusCode = -1;
        FString currencyName;
        FString errMessage;

        if (code == 0)
        {
            TSharedPtr<FJsonObject> json_object;
            auto json_reader = TJsonReaderFactory<TCHAR>::Create(UTF8_TO_TCHAR(message.c_str()));
            if (FJsonSerializer::Deserialize(json_reader, json_object))
            {
                FString statusCodeStr = json_object->GetStringField("statusCode");
                statusCode = FCString::Atoi64(*statusCodeStr);
                errMessage = json_object->GetStringField("message");
            }
        }

        if (cb != nullptr)
        {
            if (code == 0)
            {
                if (statusCode == 0)
                    cb->OnSuccess();
                else
                    cb->OnFailure(statusCode);
            }
            else
                cb->OnFailure(code);
        }
    };

    return ViveportUserStats::SetLeaderboard(
        onResult,
        std::string(TCHAR_TO_UTF8(*fName)),
        nScore);
#else
#endif
}

ULeaderboardScore UViveportUserStats::GetLeaderboardScore(int index)
{
    ULeaderboardScore uLeaderboardScore;
#if PLATFORM_WINDOWS

    if (FViveportSDKModule::IsAvailable())
    {
        LeaderboardScore leaderboardScore;
        ViveportUserStats()->GetLeaderboardScore(index, &leaderboardScore);

        uLeaderboardScore.Rank = leaderboardScore.Rank;
        uLeaderboardScore.Score = leaderboardScore.Score;
        uLeaderboardScore.UserName = UTF8_TO_TCHAR(leaderboardScore.UserName);
    }
    return uLeaderboardScore;
#elif PLATFORM_ANDROID
    int rank = ViveportUserStats::GetLeaderboardRankData(index);
    int score = ViveportUserStats::GetLeaderboardScoreData(index);
    FString name(ViveportUserStats::GetLeaderboardNameData(index).c_str());

    uLeaderboardScore.Rank = rank;
    uLeaderboardScore.Score = score;
    uLeaderboardScore.UserName = name;
    return uLeaderboardScore;
#else
#endif
}

int UViveportUserStats::GetLeaderboardScoreCount()
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        return ViveportUserStats()->GetLeaderboardScoreCount();
    }
    return 0;
#elif PLATFORM_ANDROID
    return ViveportUserStats::GetLeaderboardScoreCount();
#else
#endif
}

UELeaderboardSortMethod UViveportUserStats::GetLeaderboardSortMethod()
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        return (UELeaderboardSortMethod)ViveportUserStats()->GetLeaderboardSortMethod();
    }
    return u_ELeaderboardSortMethodNone;
#elif PLATFORM_ANDROID
    return static_cast<UELeaderboardSortMethod>(ViveportUserStats::GetLeaderboardSortType());
#else
#endif
}

UELeaderboardDisplayType UViveportUserStats::GetLeaderboardDisplayType()
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        return (UELeaderboardDisplayType)ViveportUserStats()->GetLeaderboardDisplayType();
    }
    return u_ELeaderboardDisplayTypeNumeric;
#elif PLATFORM_ANDROID
    return static_cast<UELeaderboardDisplayType>(ViveportUserStats::GetLeaderboardDisplayType());
#else
#endif
}

void IsReadyHandler(int nResult)
{
    return nResult == 0 ? is_ready_status->OnSuccess() : is_ready_status->OnFailure(nResult);
}

void DownloadStatsHandler(int nResult)
{
    return nResult == 0 ? download_stats_status->OnSuccess() : download_stats_status->OnFailure(nResult);
}

void UploadStatsHandler(int nResult)
{
    return nResult == 0 ? upload_stats_status->OnSuccess() : upload_stats_status->OnFailure(nResult);
}

void DownloadLeaderboardScoreHandler(int nResult)
{
    return nResult == 0 ? download_leaderboard_status->OnSuccess() : download_leaderboard_status->OnFailure(nResult);
}

void UploadLeaderboardScoreHandler(int nResult)
{
    return nResult == 0 ? upload_leaderboard_status->OnSuccess() : upload_leaderboard_status->OnFailure(nResult);
}