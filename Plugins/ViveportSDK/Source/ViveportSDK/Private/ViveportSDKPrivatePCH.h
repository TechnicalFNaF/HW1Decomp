// Some copyright should be here...

#pragma once

#include "CoreUObject.h"
#include "Engine.h"
#include "ViveportSDK.h"
#if PLATFORM_ANDROID
#include "ViveportSdkJni.h"
#endif

// You should place include statements to your module's private header files here.  You only need to
// add includes for headers that are used in most of your module's source files though.
DECLARE_LOG_CATEGORY_EXTERN(ViveportSDK, Log, All);