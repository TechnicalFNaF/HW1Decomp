#include "SWGVRPlayerControllerBase.h"
#include "SWGVRCharacter.h"

bool ASWGVRPlayerControllerBase::bIsUsingGamepad = false;

bool ASWGVRPlayerControllerBase::InputAxis(FKey Key, float Delta, float DeltaTime, int32 NumSamples, bool bGamepad)
{
	// I think this is accurate
	if (!bGamepad)
	{
		if (Delta <= 1.0f)
		{
			return Super::InputAxis(Key, Delta, DeltaTime, NumSamples, bGamepad);
		}
		UpdateUsingGamepadState(bGamepad);
	}

	if (Delta > 0.5)
		UpdateUsingGamepadState(bGamepad);

	return Super::InputAxis(Key, Delta, DeltaTime, NumSamples, bGamepad);
}

bool ASWGVRPlayerControllerBase::InputKey(FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad)
{
	UpdateUsingGamepadState(bGamepad);

	return Super::InputKey(Key, EventType, AmountDepressed, bGamepad);
}

void ASWGVRPlayerControllerBase::OnUsingGamepadChanged_Implementation()
{
	// Not implemented in game
}

void ASWGVRPlayerControllerBase::UpdateUsingGamepadState(bool bUsingGamepad)
{
	if (bUsingGamepad != GetStaticIsUsingGamepad())
	{
		bIsUsingGamepad = bUsingGamepad;
		OnUsingGamepadChanged();

		if (ASWGVRCharacter* SWGCharacter = Cast<ASWGVRCharacter>(GetPawn()))
		{
			SWGCharacter->OnControllerDeviceChanged.Broadcast();
		}
	}
}