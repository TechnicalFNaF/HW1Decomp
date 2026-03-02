#include "SWGVRUtil.h"

EVRPlayType USWGVRUtil::CurrentPlayType = EVRPlayType::NotUsingVR;

void USWGVRUtil::SwitchOnPlayType(EVRPlayType& VRPlayMode) 
{
	VRPlayMode = CurrentPlayType;
}

EVRPlayType USWGVRUtil::GetPlayType() 
{
    return CurrentPlayType;
}

void USWGVRUtil::ChangePlayType(EVRPlayType VRPlayMode) 
{
	CurrentPlayType = VRPlayMode;
}