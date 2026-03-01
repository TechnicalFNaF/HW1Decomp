// Fill out your copyright notice in the Description page of Project Settings.

#include "ViveportApi.h"
#include "viveport_api.h"
#include "ViveportSDKPrivatePCH.h"
#include "viveport_ext_api.h"

#define VIVEPORTSDK_VERSION "1.7.1.54"

void InitHandler(int nResult);
void ShutdownHandler(int nResult);

void GetLicenseHandler(
        const char* message,
        const char* signature
);
std::string DecodeBase64(const std::string& encoded);

static TArray<UViveportApi::LicenseChecker*> s_license_checkers;
static ViveportApiStatus* init_callback;
static ViveportApiStatus* shutdown_callback;
static std::string s_app_id;
static std::string s_app_key;
static std::string s_message;
static std::string s_signature;

int UViveportApi::Init(
        ViveportApiStatus *callback,
        const FString app_id
)
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        init_callback = callback;
        s_app_id = TCHAR_TO_UTF8(*app_id);
        return ViveportAPI()->Init(
                InitHandler,
                s_app_id.c_str()
        );
    }
    return 0;
#elif PLATFORM_ANDROID
    static ViveportApiStatus* cb = callback;
    ViveportCallback::OnResult onResult =
        [](int statusCode, std::string result)
    {
        if (statusCode == 0)
            cb->OnSuccess();
        else
            cb->OnFailure(statusCode);
    };

    return ViveportApi::Init(onResult, std::string(TCHAR_TO_UTF8(*app_id)));
#else
    return -1;
#endif
}

void UViveportApi::GetLicense(
        LicenseChecker *license_checker,
        const FString app_id,
        const FString app_key
)
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        s_license_checkers.Add(license_checker);
        s_app_id = TCHAR_TO_UTF8(*app_id);
        s_app_key = TCHAR_TO_UTF8(*app_key);
        ViveportAPI()->GetLicense(
                GetLicenseHandler,
                s_app_id.c_str(),
                s_app_key.c_str()
        );
    }
#elif PLATFORM_ANDROID
    static LicenseChecker* lc = license_checker;
    ViveportCallback::OnSuccess onSuccess =
        [](long long issueTime, long long expirationTime, int latestVersion, bool updateRequired)
    {
        lc->OnSuccess(issueTime, expirationTime, latestVersion, updateRequired);
    };
    ViveportCallback::OnFailure onFailure =
        [](int errorCode, std::string errorMessage)
    {
        lc->OnFailure(errorCode, *FString(errorMessage.c_str()));
    };

    ViveportApi::GetLicense(
        onSuccess,
        onFailure,
        std::string(TCHAR_TO_UTF8(*app_id)),
        std::string(TCHAR_TO_UTF8(*app_key)));
#else
#endif
}

int UViveportApi::Shutdown(ViveportApiStatus *callback)
{
#if PLATFORM_WINDOWS
    if (FViveportSDKModule::IsAvailable())
    {
        shutdown_callback = callback;
        return ViveportAPI()->Shutdown(ShutdownHandler);
    }
    return 0;
#elif PLATFORM_ANDROID
    static ViveportApiStatus* cb = callback;
    ViveportCallback::OnResult onResult =
        [](int statusCode, std::string result)
    {
        if (statusCode == 0)
            cb->OnSuccess();
        else
            cb->OnFailure(statusCode);
    };

    return ViveportApi::Shutdown(onResult);
#else 
    return -1;
#endif
}

FString UViveportApi::Version()
{
#if PLATFORM_WINDOWS
    auto native_version = std::string("Plugin version: ")
            .append(VIVEPORTSDK_VERSION);
    if (FViveportSDKModule::IsAvailable())
    {
        native_version.append(", Native API version: ")
                .append(ViveportAPI()->Version())
                .append(", Native Ext API version: ")
                .append(ViveportExtApi()->Version());
    }
    return FString(UTF8_TO_TCHAR(native_version.c_str()));
#elif PLATFORM_ANDROID
    return FString(UTF8_TO_TCHAR(ViveportApi::Version().c_str()));
#else
    return FString("");
#endif
}

void InitHandler(int nResult)
{
    return nResult == 0 ? init_callback->OnSuccess() : init_callback->OnFailure(nResult);
}

void ShutdownHandler(int nResult)
{
    return nResult == 0 ? shutdown_callback->OnSuccess() : shutdown_callback->OnFailure(nResult);
}


void GetLicenseHandler(
        const char* message,
        const char* signature
)
{
#if PLATFORM_WINDOWS
    auto is_verified = message != nullptr && strlen(message) > 0;
    if (!is_verified)
    {
        for (auto i = s_license_checkers.Num() - 1; i >= 0; i--)
        {
            auto checker = s_license_checkers[i];
            checker->OnFailure(
                    90003,
                    TEXT("License message is empty")
            );
            s_license_checkers.Remove(checker);
        }
        return;
    }

    is_verified = signature != nullptr && strlen(signature) > 0;
    if (!is_verified)
    {
        TSharedPtr<FJsonObject> json_object;
        auto json_reader = TJsonReaderFactory<TCHAR>::Create(UTF8_TO_TCHAR(message));
        auto error_code = 99999;
        FString error_message = TEXT("");
        if (FJsonSerializer::Deserialize(json_reader, json_object))
        {
            auto errorCodeString = json_object->GetStringField("code");
            error_code = FCString::Atoi(*errorCodeString);
            error_message = json_object->GetStringField("message");
        }

        for (auto i = s_license_checkers.Num() - 1; i >= 0; i--)
        {
            auto checker = s_license_checkers[i];
            checker->OnFailure(error_code, error_message);
            s_license_checkers.Remove(checker);
        }
        return;
    }

    s_message = std::string(message);
    s_signature = std::string(signature);

    UE_LOG(LogTemp, Display, TEXT("app_id: %s"), *FString(UTF8_TO_TCHAR(s_app_id.c_str())));
    UE_LOG(LogTemp, Display, TEXT("app_key: %s"), *FString(UTF8_TO_TCHAR(s_app_key.c_str())));
    UE_LOG(LogTemp, Display, TEXT("message: %s"), *FString(UTF8_TO_TCHAR(s_message.c_str())));
    UE_LOG(LogTemp, Display, TEXT("signature: %s"), *FString(UTF8_TO_TCHAR(s_signature.c_str())));

    auto result1 = ViveportExtLicense()->VerifyMessage(
            s_app_id.c_str(),
            s_app_key.c_str(),
            s_message.c_str(),
            s_signature.c_str()
    );
    auto wrong_app_id(s_app_id);
    wrong_app_id.append("_");
    auto result2 = ViveportExtLicense()->VerifyMessage(
            wrong_app_id.c_str(),
            s_app_key.c_str(),
            s_message.c_str(),
            s_signature.c_str()
    );

    is_verified = result1 > 0 && result2 == 0;
    if (!is_verified)
    {
        for (auto i = s_license_checkers.Num() - 1; i >= 0; i--)
        {
            auto checker = s_license_checkers[i];
            checker->OnFailure(
                    90001,
                    TEXT("License verification failed")
            );
            s_license_checkers.Remove(checker);
        }
        return;
    }

    std::string msg(s_message.c_str());
    int index = msg.find('\n');
    if (index == std::string::npos) {
        // cannot find json start!!
        index = -1;
    }
    auto encoded_json_message = msg.substr(index + 1);
    UE_LOG(LogTemp, Display, TEXT("encoded_json_message: %s"), *FString(UTF8_TO_TCHAR(encoded_json_message.c_str())));

    long long issue_time = -1;
    long long expiration_time = -1;
    auto latest_version = -1;
    auto update_required = false;

    auto json_message = DecodeBase64(std::string(encoded_json_message));
    UE_LOG(LogTemp, Display, TEXT("json_message: %s"), *FString(UTF8_TO_TCHAR(json_message.c_str())));

    TSharedPtr<FJsonObject> json_object2;
    auto json_reader2 = TJsonReaderFactory<TCHAR>::Create(UTF8_TO_TCHAR(json_message.c_str()));
    if (FJsonSerializer::Deserialize(json_reader2, json_object2))
    {
        if (json_object2->HasField("issueTime"))
        {
            auto issue_time_fstring = json_object2->GetStringField("issueTime");
            issue_time = stoll(std::string(TCHAR_TO_UTF8(*issue_time_fstring)));
        }
        if (json_object2->HasField("expirationTime"))
        {
            auto expiration_time_string = json_object2->GetStringField("expirationTime");
            expiration_time = stoll(std::string(TCHAR_TO_UTF8(*expiration_time_string)));
        }
        if (json_object2->HasField("latestVersion"))
        {
            latest_version = json_object2->GetIntegerField("latestVersion");
        }
        if (json_object2->HasField("updateRequired"))
        {
            update_required = json_object2->GetBoolField("updateRequired");
        }
    }

    for (auto i = s_license_checkers.Num() - 1; i >= 0; i--)
    {
        auto checker = s_license_checkers[i];
        checker->OnSuccess(
                issue_time,
                expiration_time,
                latest_version,
                update_required
        );
        s_license_checkers.Remove(checker);
    }
#endif
}

std::string DecodeBase64(const std::string& encoded)
{
#if PLATFORM_WINDOWS
    static const char reverse_table[128] = {
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63,
        52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64, 64, 64, 64,
        64,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
        15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64,
        64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
        41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64
    };

    std::string result;
    const auto last = encoded.end();
    auto bits_collected = 0;
    unsigned int accumulator = 0;

    for (auto i = encoded.begin(); i != last; ++i) {
        const int c = *i;
        if (isspace(c) || c == '=') {
            // Skip whitespace and padding. Be liberal in what you accept.
            continue;
        }
        if ((c > 127) || (c < 0) || (reverse_table[c] > 63)) {
            UE_LOG(LogTemp, Warning, TEXT("This contains characters not legal in a base64 encoded string."));
            continue;
        }
        accumulator = (accumulator << 6) | reverse_table[c];
        bits_collected += 6;
        if (bits_collected >= 8) {
            bits_collected -= 8;
            result += static_cast<char>((accumulator >> bits_collected) & 0xffu);
        }
    }
    return result;
#else
    return std::string("");
#endif
}
