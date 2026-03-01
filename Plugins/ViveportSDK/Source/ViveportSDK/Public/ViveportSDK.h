// Some copyright should be here...

#pragma once

#include <string>
#include "Modules/ModuleManager.h"

//#include "C:/NVPACK/jdk1.8.0_77/include/jni.h"
//#include "C:/NVPACK/jdk1.8.0_77/include/win32/jni_md.h"


class FViveportSDKModule : public IModuleInterface
{
public:

    /** IModuleInterface implementation */
    void StartupModule() override;
    void ShutdownModule() override;

    /**
    * Singleton-like access to this module's interface.  This is just for convenience!
    * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
    *
    * @return Returns singleton instance, loading the module on demand if needed
    */
    static FViveportSDKModule& Get()
    {
        return FModuleManager::LoadModuleChecked< FViveportSDKModule >("ViveportSDK");
    }

    /**
    * Checks to see if this module is loaded and ready.  It is only valid to call Get()
    * if IsAvailable() returns true.
    *
    * @return True if the module is loaded and ready to use
    */
    static bool IsAvailable()
    {
        auto is_available = FModuleManager::Get().IsModuleLoaded("ViveportSDK");
#if PLATFORM_WINDOWS
        if (is_available) {
            // Concatenate the plugins folder and the DLL file.
            auto file_path1 = FPaths::Combine(
                    *FPaths::ProjectDir(),
                    TEXT("Plugins/ViveportSDK/ThirdParty/Viveport/Libraries/Win32"),
                    TEXT("viveport_api.dll")
            );
            auto dll_handle1 = FPlatformProcess::GetDllHandle(*file_path1);
            if (dll_handle1 == nullptr) {
                file_path1 = FPaths::Combine(
                        *FPaths::ProjectDir(),
                        TEXT("Plugins/ViveportSDK/ThirdParty/Viveport/Libraries/Win64"),
                        TEXT("viveport_api64.dll")
                );
                FPlatformProcess::GetDllHandle(*file_path1);
            }

            auto file_path2 = FPaths::Combine(
                *FPaths::ProjectDir(),
                TEXT("Plugins/ViveportSDK/ThirdParty/Viveport/Libraries/Win32"),
                TEXT("viveport_ext_api.dll")
                );
            auto dll_handle2 = FPlatformProcess::GetDllHandle(*file_path2);
            if (dll_handle2 == nullptr) {
                file_path2 = FPaths::Combine(
                    *FPaths::ProjectDir(),
                    TEXT("Plugins/ViveportSDK/ThirdParty/Viveport/Libraries/Win64"),
                    TEXT("viveport_ext_api64.dll")
                    );
                FPlatformProcess::GetDllHandle(*file_path2);
            }
        }
#endif
        return is_available;
    }
};