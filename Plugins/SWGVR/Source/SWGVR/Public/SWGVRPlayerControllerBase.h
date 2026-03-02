#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SWGVRPlayerControllerBase.generated.h"

UCLASS()
class SWGVR_API ASWGVRPlayerControllerBase : public APlayerController 
{
    GENERATED_BODY()
public:

	static FORCEINLINE bool GetStaticIsUsingGamepad()
	{
		return bIsUsingGamepad;
	};

	UFUNCTION(BlueprintPure)
	bool IsUsingGamepad()
	{
		return GetStaticIsUsingGamepad();
	};
	
	virtual bool InputAxis(FKey Key, float Delta, float DeltaTime, int32 NumSamples, bool bGamepad) override;
	virtual bool InputKey(FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad) override;

protected:

	UFUNCTION(BlueprintNativeEvent)
	void OnUsingGamepadChanged();

private:
	
	void UpdateUsingGamepadState(bool);

	static bool bIsUsingGamepad;
};