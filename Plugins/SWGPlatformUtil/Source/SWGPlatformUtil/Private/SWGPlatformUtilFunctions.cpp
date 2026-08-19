#include "SWGPlatformUtilFunctions.h"

#include "SWGPlatformSettings.h"

// Matching
const FString& USWGPlatformUtilFunctions::GetVersionString() 
{
	static FString VersionString = {TEXT("unversioned")};
	return VersionString;
}