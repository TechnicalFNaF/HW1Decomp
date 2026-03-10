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

	// TODO Not matching
	UFUNCTION(BlueprintCallable, meta=(ExpandEnumAsExecs="VRPlayMode"))
	static void SwitchOnPlayType(EVRPlayType& VRPlayMode)
	{
		VRPlayMode = CurrentPlayType;
	}
	
	// TODO Not matching
	UFUNCTION(BlueprintPure)
	static EVRPlayType GetPlayType()
	{
		return CurrentPlayType;
	}

	// TODO Not matching
	UFUNCTION(BlueprintCallable)
	static void ChangePlayType(EVRPlayType VRPlayMode)
	{
		CurrentPlayType = VRPlayMode;
	}
	
	static EVRPlayType CurrentPlayType;
};

