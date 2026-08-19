#include "SWGVRPlayerControllerBase.h"
#include "SWGVRCharacter.h"

bool ASWGVRPlayerControllerBase::bIsUsingGamepad; // game does not initialize this

// Matching
bool ASWGVRPlayerControllerBase::InputAxis(FKey Key, float Delta, float DeltaTime, int32 NumSamples, bool bGamepad)
{
	if ((bGamepad && Delta > 0.5f) || (!bGamepad && Delta > 1.0f))
		UpdateUsingGamepadState(bGamepad);
	
	return Super::InputAxis(Key, Delta, DeltaTime, NumSamples, bGamepad);
}

// Matching 
bool ASWGVRPlayerControllerBase::InputKey(FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad)
{
	UpdateUsingGamepadState(bGamepad);

	return Super::InputKey(Key, EventType, AmountDepressed, bGamepad);
}

// Matching
void ASWGVRPlayerControllerBase::OnUsingGamepadChanged_Implementation()
{

}

// Matching
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