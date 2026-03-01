//
// Created by Jake_Hu on 2018/1/31.
//

#include <string>
#include <jni.h>


class ViveportCallback {
public:
    ViveportCallback();
    ~ViveportCallback();

    typedef void(*OnResult)(int statusCode, std::string result);
    typedef void(*OnGetLicense)(std::string message, std::string signature);
    typedef void(*OnSuccess)(long long issueTime, long long expirationTime, int latestVersion, bool updateRequired);
    typedef void(*OnFailure)(int errorCode, std::string errorMessage);
};

class ViveportCallback2{
public:
    ViveportCallback2();
    ~ViveportCallback2();

    typedef void(*OnSuccess)();
    typedef void(*OnFailure)(int errorCode, std::string errorMessage);
};

class ViveportSdkJni{
public:
    static jobject GetGlobalContext(JNIEnv* env);
    static JNIEnv* GetJavaEnv();
    static void DetachJavaEnv();
    static jclass FindJavaClass(const char* name);
};

class ViveportApi {
public:
    ViveportApi();
    ~ViveportApi();

    static int Init(
            ViveportCallback::OnResult onResult,
            std::string appId);

    static void GetLicense(
            ViveportCallback::OnGetLicense onGetLicense,
            std::string appId,
            std::string appKey);

    static void GetLicense(
            ViveportCallback::OnSuccess onSuccess,
            ViveportCallback::OnFailure onFailure,
            std::string appId,
            std::string appKey);

    static int Shutdown(
            ViveportCallback::OnResult onResult);

    static std::string Version();
};

class ViveportIAPurchase {
public:
    ViveportIAPurchase();
    ~ViveportIAPurchase();

    static void IsReady(
            ViveportCallback::OnResult onResult,
            std::string appKey);

    static void MakePurchase(
            ViveportCallback::OnResult onResult,
            std::string purchaseID);

    static void Query(
            ViveportCallback::OnResult onResult,
            std::string purchaseID);

    static void Query(
            ViveportCallback::OnResult  onResult);

    static void Request(
            ViveportCallback::OnResult onResult,
            std::string price);

    static void Request(
            ViveportCallback::OnResult onResult,
            std::string price,
            std::string userData);

    static void GetBalance(
            ViveportCallback::OnResult onResult);

    static void SubScribe(
            ViveportCallback::OnResult onResult,
            std::string subscriptionID);

    static void QuerySubscription(
            ViveportCallback::OnResult onResult,
            std::string subscriptionID);

    static void QuerySubscriptionList(
            ViveportCallback::OnResult onResult);

    static void RequestSubscription(
            ViveportCallback::OnResult onResult,
            std::string price,
            std::string freeTrialType,
            int freeTrialValue,
            std::string chargePeriodType,
            int chargePeriodValue,
            int numberOfChargePeriod,
            std::string planID);

    static void RequestSubscriptionWithPlanId(
            ViveportCallback::OnResult onResult,
            std::string planID);

    static void CancelSubscription(
            ViveportCallback::OnResult onResult,
            std::string subscriptionID);

    static void SendPrepareOverlaySceneChange(
            ViveportCallback::OnResult onResult,
            std::string messageToSend);

    static void SendOverlayMessagePurchaseEnd(
            ViveportCallback::OnResult onResult,
            std::string messageToSend);

    static void SendOverlayMessagePurchaseItem(
            ViveportCallback::OnResult onResult,
            std::string messageToSend);

    static void SendOverlayMessageLaunchNotify(
            ViveportCallback::OnResult onResult,
            std::string messageToSend);
};

class ViveportUser {
public:
    ViveportUser();
    ~ViveportUser();

    static int IsReady(
            ViveportCallback::OnResult onResult);

    static std::string GetUserID();

    static std::string GetUserName();

    static std::string GetUserAvatar();
};

class ViveportSubscription {
public:
    ViveportSubscription();
    ~ViveportSubscription();

    static void IsReady(ViveportCallback::OnResult onResult);
    static bool IsWindowsSubscriber();
    static bool IsAndroidSubscriber();
    static int GetTransactionType();
};

class ViveportSessionToken {
public:
    ViveportSessionToken();
    ~ViveportSessionToken();

    static void IsReady(ViveportCallback::OnResult onResult);
    static void GetSessionToken(ViveportCallback::OnResult onResult);

};

class ViveportDeeplink{
public:
    ViveportDeeplink();
    ~ViveportDeeplink();

    static void GoToApp(
            ViveportCallback2::OnSuccess onSuccess,
            ViveportCallback2::OnFailure onFailure,
            std::string viveportId,
            std::string launchData);

    static void GoToStore(
            ViveportCallback2::OnSuccess onSuccess,
            ViveportCallback2::OnFailure onFailure,
            std::string viveportId);

    static void GoToAppOrGoToStore(
            ViveportCallback2::OnSuccess onSuccess,
            ViveportCallback2::OnFailure onFailure,
            std::string viveportId,
            std::string launchData);

    static std::string GetAppLaunchData(jobject inActivity);
};

class ViveportUserStats {
public:
    ViveportUserStats();
    ~ViveportUserStats();

    static int IsReady(
            ViveportCallback::OnResult onResult);

    static int GetLeaderboard(
            ViveportCallback::OnResult onResult,
            std::string leaderboardName,
            int start,
            int end,
            int timeRange,
            int dataType);

    static int SetLeaderboard(
            ViveportCallback::OnResult onResult,
            std::string leaderboardName,
            int score);

    static int DownloadStats(
            ViveportCallback::OnResult onResult);

    static int UploadStats(
            ViveportCallback::OnResult onResult);


    static std::string GetLeaderboardNameData(
            int index);

    static int GetLeaderboardRankData(
            int index);

    static int GetLeaderboardScoreData(
            int index);

    static int GetLeaderboardSortType();

    static int GetLeaderboardDisplayType();

    static int GetLeaderboardScoreCount();

    static float GetStats(
            std::string key,
            float value);

    static int GetStats(
            std::string key,
            int value);

    static int SetStats(
            std::string key,
            int value);

    static int SetStats(
            std::string key,
            float value);

    static bool GetAchievement(
            std::string name);

    static int SetAchievement(
            std::string name);

    static int ClearAchievement(
            std::string name);

    static int GetAchievementUnlockTime(
            std::string name);
};