#pragma once

#if defined( _WIN32 )
#if defined( viveport_api_STATIC )
#define VIVEPORT_API extern "C"
#elif defined(viveport_api_EXPORTS)
#define VIVEPORT_API extern "C" __declspec(dllexport)
#else  // viveport_api_EXPORTS
#define VIVEPORT_API extern "C" __declspec(dllimport)
#endif // viveport_api_EXPORTS
#elif defined( __GNUC__ )
#define __cdecl    /* nothing */
#define __fastcall /* nothing */
#define __stdcall  /* nothing */
#ifdef viveport_api_EXPORTS
#define VIVEPORT_API extern "C" __attribute__ ((visibility("default")))
#else  // viveport_api_EXPORTS
#define VIVEPORT_API extern "C"
#endif // viveport_api_EXPORTS
#else // !_WIN32
#define __cdecl    /* nothing */
#define __fastcall /* nothing */
#define __stdcall  /* nothing */
#ifdef viveport_api_EXPORTS
#define VIVEPORT_API extern "C"
#else  // viveport_api_EXPORTS
#define VIVEPORT_API extern "C"
#endif // viveport_api_EXPORTS
#endif

#define VIVEPORT_VR "ViveportVR"
#define VIVE_VIDEO "ViveVideo"

/**
 * Top-level API
 */
// General status callback
typedef void(*StatusCallback)(int nResult);

typedef void(*ViveportGetLicenseCallback)(const char* message, const char* signature);

typedef void(*StatusCallback2)(int nResult, const char* message);

enum ERuntimeMode
{
    k_EOther_Unknown = -1,   // unknow mode
    k_EDefalut = 0,         // older version pc client 
    k_EViveportDesktop = 1,    // viveport Desktop
    k_EViveportArcade = 2,    // ViveportArcade
};
typedef void(*ViveportQueryRuntimeMode)(int nResult, ERuntimeMode emu);

struct IViveportAPI
{
    //virtual int RestartAppIfNecessary(float) = 0;
    virtual int Init(StatusCallback callback, const char *pGameID) = 0;
    virtual void GetLicense(ViveportGetLicenseCallback callback, const char* appid, const char* appkey) = 0;
    virtual int Shutdown(StatusCallback callback) = 0;
    virtual const char* Version() = 0;
    virtual void QueryRuntimeMode(ViveportQueryRuntimeMode QueryRuntimeCB) = 0;
};

VIVEPORT_API IViveportAPI* ViveportAPI();
VIVEPORT_API int IViveportAPI_Init(StatusCallback InitCB, const char * pGameID);
VIVEPORT_API void IViveportAPI_GetLicense(ViveportGetLicenseCallback callback, const char* appid, const char* appkey);
VIVEPORT_API int IViveportAPI_Shutdown(StatusCallback ShutdownCB);
VIVEPORT_API const char* IViveportAPI_Version();
VIVEPORT_API void IViveportAPI_QueryRuntimeMode(ViveportQueryRuntimeMode QueryRuntimeModeCB);

/**
* Token API
*/
struct IViveportToken
{
    virtual int IsReady(StatusCallback) = 0;
    virtual int GetSessionToken(StatusCallback2) = 0;
};

VIVEPORT_API IViveportToken* ViveportToken();
VIVEPORT_API int IViveportToken_IsReady(StatusCallback cb);
VIVEPORT_API int IViveportToken_GetSessionToken(StatusCallback2 cb);

/**
 * User API
 */
struct IViveportUser
{
    virtual int IsReady(StatusCallback) = 0;
    virtual int GetUserID(char*, int) = 0;
    virtual int GetUserName(char*, int) = 0;
    virtual int GetUserAvatarUrl(char*, int) = 0;
};

VIVEPORT_API IViveportUser* ViveportUser();

VIVEPORT_API int IViveportUser_IsReady(StatusCallback fn);
VIVEPORT_API int IViveportUser_GetUserID(char* userID, int size);
VIVEPORT_API int IViveportUser_GetUserName(char* userName, int size);
VIVEPORT_API int IViveportUser_GetUserAvatarUrl(char* userAvatarUrl, int size);

/**
 * UserStats API
 */


enum ELeaderboardDataDownload
{
    k_ELeaderboardDataDownloadGlobal = 0,
    k_ELeaderboardDataDownloadGlobalAroundUser = 1,
    k_ELeaderboardDataDownloadLocal = 2,
    k_ELeaderboardDataDownloadLocaleAroundUser = 3,
};

enum ELeaderboardDataTimeRange
{
    k_ELeaderboardDataScropeAllTime = 0,
    k_ELeaderboardDataScropeDaily = 1,
    k_ELeaderboardDataScropeWeekly = 2,
    k_ELeaderboardDataScropeMonthly = 3,
};

enum ELeaderboardSortMethod
{
    k_ELeaderboardSortMethodNone,
    k_ELeaderboardSortMethodAscending,
    k_ELeaderboardSortMethodDescending,
};

enum ELeaderboardDisplayType
{
    k_ELeaderboardDisplayTypeNone = 0,
    k_ELeaderboardDisplayTypeNumeric = 1,            // simple numerical score
    k_ELeaderboardDisplayTypeTimeSeconds = 2,        // the score represents a time, in seconds
    k_ELeaderboardDisplayTypeTimeMilliSeconds = 3,    // the score represents a time, in milliseconds
};

enum ELeaderboardUploadScoreMethod
{
    k_ELeaderboardUploadScoreMethodNone = 0,
    k_ELeaderboardUploadScoreMethodKeepBest = 1,    // Leaderboard will keep user's best score
    k_ELeaderboardUploadScoreMethodForceUpdate = 2,    // Leaderboard will always replace score with specified
};

struct LeaderboardScore
{
    int        Rank;    // [1..N], where N is the number of users with an entry in the leaderboard
    int        Score;            // score as set in the leaderboard
    char       UserName[64];        // the user name showing in the leaderboard 
};

// asks the Steam back-end for a leaderboard by name, and will create it if it's not yet
// This call is asynchronous, with the result returned in LeaderboardFindResult_t
typedef void(*FindOrCreateLeaderboard)(const char *pchLeaderboardName, ELeaderboardSortMethod eLeaderboardSortMethod, ELeaderboardDisplayType eLeaderboardDisplayType);
// as above, but won't create the leaderboard if it's not found
// This call is asynchronous, with the result returned in LeaderboardFindResult_t
typedef void(*FindLeaderboard)(const char *pchLeaderboardName);

struct IViveportUserStats
{
    virtual int IsReady(StatusCallback) = 0;
    // Ask the server to send down this user's data and achievements for this game
    virtual int DownloadStats(StatusCallback) = 0;
    virtual int UploadStats(StatusCallback) = 0;

    /********************************************************/
    /*                Stats functions                        */
    /********************************************************/
    // Data accessors
    virtual int GetStat(const char *, int *) = 0;
    virtual int GetStat(const char *, float *) = 0;
    virtual int SetStat(const char *, int) = 0;
    virtual int SetStat(const char *, float) = 0;

    /*********************************************************/
    /*                Leaderboard functions                  */
    /*********************************************************/
    virtual int DownloadLeaderboardScores(StatusCallback, const char *pchLeaderboardName, ELeaderboardDataDownload eLeaderboardDataDownload, ELeaderboardDataTimeRange eLeaderboardDataTimeRange, int nRangeStart, int nRangeEnd) = 0;
    virtual int UploadLeaderboardScore(StatusCallback, const char *pchLeaderboardName, int nScore) = 0;
    virtual int GetLeaderboardScore(int index, LeaderboardScore *pLeaderboardScore) = 0;
    virtual int GetLeaderboardScoreCount() = 0;
    virtual ELeaderboardSortMethod GetLeaderboardSortMethod() = 0;
    virtual ELeaderboardDisplayType GetLeaderboardDisplayType() = 0;

    /*********************************************************/
    /*                Achievement functions                  */
    /*********************************************************/
    virtual int GetAchievement(const char *pchName, int *pbAchieved) = 0;
    virtual const char * GetAchievementDisplayAttribute(const char *pchName, const char *pchKey) = 0;
    //virtual int GetAchievementIcon(const char *pchName) = 0;
    virtual int GetAchievementUnlockTime(const char *pchName, int *punUnlockTime) = 0;
    virtual int SetAchievement(const char *pchName) = 0;
    virtual int ClearAchievement(const char *pchName) = 0;
};

VIVEPORT_API IViveportUserStats* ViveportUserStats();
VIVEPORT_API int IViveportUserStats_IsReady(StatusCallback IsReadyCB);
VIVEPORT_API int IViveportUserStats_DownloadStats(StatusCallback DownloadCurrentStatCB);
VIVEPORT_API int IViveportUserStats_GetStat0(const char *pchName, int *pnData);
VIVEPORT_API int IViveportUserStats_GetStat(const char *pchName, float *pfData);
VIVEPORT_API int IViveportUserStats_SetStat0(const char *pchName, int nData);
VIVEPORT_API int IViveportUserStats_SetStat(const char *pchName, float nData);
VIVEPORT_API int IViveportUserStats_UploadStats(StatusCallback UploadStatsCB);
VIVEPORT_API int IViveportUserStats_DownloadLeaderboardScores(StatusCallback, const char *pchLeaderboardName, ELeaderboardDataDownload eLeaderboardDataDownload, ELeaderboardDataTimeRange eLeaderboardDataTimeRange, int nRangeStart, int nRangeEnd);
VIVEPORT_API int IViveportUserStats_UploadLeaderboardScore(StatusCallback, const char *pchLeaderboardName, int nScore);
VIVEPORT_API int IViveportUserStats_GetLeaderboardScore(int index, LeaderboardScore *pLeaderboardScore);
VIVEPORT_API int IViveportUserStats_GetLeaderboardScoreCount();
VIVEPORT_API ELeaderboardSortMethod IViveportUserStats_GetLeaderboardSortMethod();
VIVEPORT_API ELeaderboardDisplayType IViveportUserStats_GetLeaderboardDisplayType();
VIVEPORT_API int IViveportUserStats_GetAchievement(const char *pchName, int *pbAchieved);
VIVEPORT_API int IViveportUserStats_GetAchievementUnlockTime(const char *pchName, int *punUnlockTime);
VIVEPORT_API int IViveportUserStats_SetAchievement(const char *pchName);
VIVEPORT_API int IViveportUserStats_ClearAchievement(const char *pchName);

/**
* In-App Purchase API
*/
typedef void(*ViveportIAPurchaseCallback)(int nCode, const char *pchMessage);

struct ViveportIAPCurrency
{
    char name[16];
    char symbol[16];
};

struct IViveportIAPurchase
{
    virtual void IsReady(ViveportIAPurchaseCallback callback, const char *pchAppKey) = 0;
    virtual void Purchase(ViveportIAPurchaseCallback callback, const char *pchPurchaseId) = 0;
    virtual void Query(ViveportIAPurchaseCallback callback, const char *pchPurchaseId) = 0;
    virtual void Query(ViveportIAPurchaseCallback callback) = 0;
    virtual void Request(ViveportIAPurchaseCallback callback, const char *pchPrice) = 0;
    virtual void RequestWithUserData(ViveportIAPurchaseCallback callback, const char *pchPrice, const char *pchUserData) = 0;
    virtual void GetCurrency(ViveportIAPCurrency *pCurrency) = 0;
    virtual void GetBalance(ViveportIAPurchaseCallback callback) = 0;

    virtual void Subscribe(ViveportIAPurchaseCallback callback, const char *pchSubscriptionId) = 0;
    virtual void QuerySubscription(ViveportIAPurchaseCallback callback, const char *pchSubscriptionId) = 0;
    virtual void QuerySubscriptionList(ViveportIAPurchaseCallback callback) = 0;
    virtual void RequestSubscription(ViveportIAPurchaseCallback callback, const char *pchPrice, const char *pFreeTrialType, int nFreeTrialValue,
        const char *pchChargePeriodType, int nChargePeriodValue, int nNumberOfChargePeriod, const char *pchPlanId) = 0;
    virtual void RequestSubscriptionWithPlanID(ViveportIAPurchaseCallback callback, const char *pchPlanId) = 0;
    virtual void CancelSubscription(ViveportIAPurchaseCallback callback, const char *pchSubscriptionId) = 0;
};

VIVEPORT_API IViveportIAPurchase* ViveportIAPurchase();
VIVEPORT_API void IViveportIAPurchase_IsReady(ViveportIAPurchaseCallback callback, const char *pAppKey);
VIVEPORT_API void IViveportIAPurchase_Purchase(ViveportIAPurchaseCallback callback, const char *pchPurchaseId);
VIVEPORT_API void IViveportIAPurchase_Query(ViveportIAPurchaseCallback callback, const char *pchPurchaseId);
VIVEPORT_API void IViveportIAPurchase_QueryList(ViveportIAPurchaseCallback callback);
VIVEPORT_API void IViveportIAPurchase_Request(ViveportIAPurchaseCallback callback, const char *pchPrice);
VIVEPORT_API void IViveportIAPurchase_RequestWithUserData(ViveportIAPurchaseCallback callback, const char *pchPrice, const char *pchUserData);
VIVEPORT_API void IViveportIAPurchase_GetBalance(ViveportIAPurchaseCallback callback);

VIVEPORT_API void IViveportIAPurchase_Subscribe(ViveportIAPurchaseCallback callback, const char *pchSubscriptionId);
VIVEPORT_API void IViveportIAPurchase_QuerySubscription(ViveportIAPurchaseCallback callback, const char *pchSubscriptionId);
VIVEPORT_API void IViveportIAPurchase_QuerySubscriptionList(ViveportIAPurchaseCallback callback);
VIVEPORT_API void IViveportIAPurchase_RequestSubscription(ViveportIAPurchaseCallback callback, const char *pchPrice, const char *pchFreeTrialType, int nFreeTrialValue,
    const char *pchChargePeriodType, int nChargePeriodValue, int nNumberOfChargePeriod, const char *pchPlanId);
VIVEPORT_API void IViveportIAPurchase_RequestSubscriptionWithPlanID(ViveportIAPurchaseCallback callback, const char *pchPlanId);
VIVEPORT_API void IViveportIAPurchase_CancelSubscription(ViveportIAPurchaseCallback callback, const char *pchSubscriptionId);

struct IViveportArcadeLeaderboard
{
    virtual void IsReady(StatusCallback) = 0;
    virtual void DownloadLeaderboardScores(StatusCallback, const char *pchLeaderboardName, ELeaderboardDataTimeRange eLeaderboardDataTimeRange, int nCount) = 0;
    virtual void UploadLeaderboardScore(StatusCallback, const char *pchLeaderboardName, const char *pchUserName, int nScore) = 0;
    virtual int GetLeaderboardUserRank() = 0;
    virtual int GetLeaderboardUserScore() = 0;
    virtual int GetLeaderboardScoreCount() = 0;
    virtual void GetLeaderboardScore(int index, LeaderboardScore *pLeaderboardScore) = 0;
};

VIVEPORT_API IViveportArcadeLeaderboard* ViveportArcadeLeaderboard();
VIVEPORT_API void IViveportArcadeLeaderboard_IsReady(StatusCallback fn);
VIVEPORT_API void IViveportArcadeLeaderboard_DownloadLeaderboardScores(StatusCallback, const char *pchLeaderboardName, ELeaderboardDataTimeRange eLeaderboardDataTimeRange, int nCount);
VIVEPORT_API void IViveportArcadeLeaderboard_UploadLeaderboardScore(StatusCallback UploadLeaderboardScoreCB, const char *pchLeaderboardName, const char *pchUserName, int nScore);
VIVEPORT_API int IViveportArcadeLeaderboard_GetLeaderboardUserRank();
VIVEPORT_API int IViveportArcadeLeaderboard_GetLeaderboardUserScore();
VIVEPORT_API int IViveportArcadeLeaderboard_GetLeaderboardScoreCount();
VIVEPORT_API void IViveportArcadeLeaderboard_GetLeaderboardScore(int index, LeaderboardScore *pLeaderboardScore);

/**
* ViveportArcadeSession API
*/
typedef void(*ViveportArcadeSessionCallback)(int nCode, const char *pchMessage);
struct IViveportArcadeSession
{
    virtual void IsReady(ViveportArcadeSessionCallback callback) = 0;
    virtual void Start(ViveportArcadeSessionCallback callback) = 0;
    virtual void Stop(ViveportArcadeSessionCallback callback) = 0;
};

VIVEPORT_API IViveportArcadeSession* ViveportArcadeSession();
VIVEPORT_API void IViveportArcadeSession_IsReady(ViveportArcadeSessionCallback callback);
VIVEPORT_API void IViveportArcadeSession_Start(ViveportArcadeSessionCallback callback);
VIVEPORT_API void IViveportArcadeSession_Stop(ViveportArcadeSessionCallback callback);

/**
* DLC API
*/
struct IViveportDlc
{
	virtual int IsReady(StatusCallback) = 0;
	virtual int GetCount() = 0;
	virtual bool GetIsAvailable(int index, char* appId, bool &isAvailable) = 0;
    virtual int IsSubscribed() = 0;
};

VIVEPORT_API IViveportDlc* ViveportDlc();
VIVEPORT_API int IViveportDlc_IsReady(StatusCallback cb);
VIVEPORT_API int IViveportDlc_GetCount();
VIVEPORT_API bool IViveportDlc_GetIsAvailable(int index, char* appId, bool &isAvailable);
VIVEPORT_API int IViveportDlc_IsSubscribed();

/**
* Subscription API
*/

enum ESubscriptionTransactionType
{
    UNKNOWN = 0,
    PAID = 1,
    REDEEM = 2,
    FREE_TRIAL = 3
};

struct IViveportSubscription
{
    virtual void IsReady(StatusCallback2 callback) = 0;
    virtual bool IsWindowsSubscriber() = 0;
    virtual bool IsAndroidSubscriber() = 0;
    virtual ESubscriptionTransactionType GetTransactionType() = 0;
};

VIVEPORT_API IViveportSubscription* ViveportSubscription();
VIVEPORT_API void IViveportSubscription_IsReady(StatusCallback2 callback);
VIVEPORT_API bool IViveportSubscription_IsWindowsSubscriber();
VIVEPORT_API bool IViveportSubscription_IsAndroidSubscriber();
VIVEPORT_API ESubscriptionTransactionType IViveportSubscription_GetTransactionType();

/**
* Deeplink API
*/

enum EDeeplinkPlatform
{
    VIVEPORT = 0,
    STEAM = 1,
    NOT_SUPPORT = 2
};

struct IViveportDeeplink
{
    virtual void IsReady(StatusCallback cb) = 0;
    virtual void GoToApp(StatusCallback2 cb, const char* viveportId, const char* launchData) = 0;
    virtual void GoToApp(StatusCallback2 cb, const char* viveportId, const char* launchData, const char* branchName) = 0;
    virtual void GoToStore(StatusCallback2 cb, const char* viveportId) = 0;
    virtual void GoToAppOrGoToStore(StatusCallback2 cb, const char* viveportId, const char* launchData) = 0;
    virtual int GetAppLaunchData(char* userID, int size) = 0;
};

VIVEPORT_API IViveportDeeplink* ViveportDeeplink();
VIVEPORT_API void IViveportDeeplink_IsReady(StatusCallback cb);
VIVEPORT_API void IViveportDeeplink_GoToApp(StatusCallback2 cb, const char* viveportId, const char* launchData);
VIVEPORT_API void IViveportDeeplink_GoToAppWithBranchName(StatusCallback2 cb, const char* viveportId, const char* launchData, const char* branchName);
VIVEPORT_API void IViveportDeeplink_GoToStore(StatusCallback2 cb, const char* viveportId);
VIVEPORT_API void IViveportDeeplink_GoToAppOrGoToStore(StatusCallback2 cb, const char* viveportId, const char* launchData);
VIVEPORT_API int IViveportDeeplink_GetAppLaunchData(char* userID, int size);

/**
* Social API
*/

struct IViveportSocial
{
    virtual void GetInAppFriendList(StatusCallback2 callback, const char* viveportKey) = 0;
    virtual void RegisterFriendRequestCountCallback(StatusCallback2 callback, const char* viveportKey) = 0;
    virtual void GetUserProfile(StatusCallback2 callback, const char* viveportKey) = 0;
    virtual void GetUserProfileWithId(StatusCallback2 callback, const char* publidId, const char* viveportKey) = 0;
    virtual void ShowSendFriendRequestOverlay(const char* publicId, const char* viveportKey) = 0;
    virtual void ShowPendingFriendRequestListOverlay(const char* viveportKey) = 0;
    virtual void GetUserConsentStatus(StatusCallback2 callback, const char* viveportKey) = 0;
    virtual void ShowConsentOverlay(StatusCallback2 callback, const char* viveportKey) = 0;
};

VIVEPORT_API IViveportSocial* ViveportSocial();
VIVEPORT_API void IViveportSocial_GetInAppFriendList(StatusCallback2 callback, const char* viveportKey);
VIVEPORT_API void IViveportSocial_RegisterFriendRequestCountCallback(StatusCallback2 callback, const char* viveportKey);
VIVEPORT_API void IViveportSocial_GetUserProfile(StatusCallback2 callback, const char* viveportKey);
VIVEPORT_API void IViveportSocial_GetUserProfileWithId(StatusCallback2 callback, const char* publicId, const char* viveportKey);
VIVEPORT_API void IViveportSocial_ShowSendFriendRequestOverlay(const char* publicId, const char* viveportKey);
VIVEPORT_API void IViveportSocial_ShowPendingFriendRequestListOverlay(const char* viveportKey);
VIVEPORT_API void IViveportSocial_GetUserConsentStatus(StatusCallback2 callback, const char* viveportKey);
VIVEPORT_API void IViveportSocial_ShowConsentOverlay(StatusCallback2 callback, const char* viveportKey);
