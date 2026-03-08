#include "SWGVRUtil.h"

EVRPlayType USWGVRUtil::CurrentPlayType = EVRPlayType::NotUsingVR;

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
void USWGVRUtil::ChangePlayType(EVRPlayType VRPlayMode) 
{
	CurrentPlayType = VRPlayMode;
}