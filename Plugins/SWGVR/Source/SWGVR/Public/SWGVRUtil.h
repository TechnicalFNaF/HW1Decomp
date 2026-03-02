#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SWGVRUtil.generated.h"

UENUM()
enum class EVRPlayType : uint8 
{
    UsingVR,
    NotUsingVR,
};

UCLASS(BlueprintType)
class SWGVR_API USWGVRUtil : public UBlueprintFunctionLibrary 
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, meta=(ExpandEnumAsExecs="VRPlayMode"))
    static void SwitchOnPlayType(EVRPlayType& VRPlayMode);
    
    UFUNCTION(BlueprintPure)
    static EVRPlayType GetPlayType();
    
    UFUNCTION(BlueprintCallable)
    static void ChangePlayType(EVRPlayType VRPlayMode);
    
    static EVRPlayType CurrentPlayType;
};

