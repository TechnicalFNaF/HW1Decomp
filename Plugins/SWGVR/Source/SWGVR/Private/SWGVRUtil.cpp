#include "SWGVRUtil.h"

EVRPlayType USWGVRUtil::CurrentPlayType; // game does not initialize this

// Matching
void USWGVRUtil::SwitchOnPlayType(EVRPlayType& VRPlayMode)
{
	VRPlayMode = CurrentPlayType;
}

// Matching
EVRPlayType USWGVRUtil::GetPlayType()
{
	return CurrentPlayType;
}

// Matching
FORCENOINLINE void USWGVRUtil::ChangePlayType(EVRPlayType VRPlayMode)
{
	CurrentPlayType = VRPlayMode;
}