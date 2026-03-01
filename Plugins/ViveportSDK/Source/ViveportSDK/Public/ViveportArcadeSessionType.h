#pragma once
#include "CoreUObject.h"
#include "ViveportArcadeSessionType.generated.h"


USTRUCT()
struct FSessionResult
{
    GENERATED_BODY()

    UPROPERTY()
        FString pchAppID;

    UPROPERTY()
        FString pchGuid;
};
/**
*	Callback of Viveport Arcade Session APIs
*/
class SessionListener
{
public:
    virtual ~SessionListener() { }

    virtual void OnSuccess(const FString& pchAppID) { }
    virtual	void OnStartSuccess(const FString& pchAppID, const FString& pchGuid) { }
    virtual void OnStopSuccess(const FString& pchAppID, const FString& pchGuid) { }
    virtual void OnFailure(int nCode, const FString& pchMessage) { }

protected:
    SessionListener() { }
};