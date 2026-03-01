// Some copyright should be here...

using UnrealBuildTool;
using System.IO;

public class ViveportSDK : ModuleRules
{
    private string ModulePath
    {
        get { return ModuleDirectory; }
    }

    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/")); }
    }

#if !WITH_FORWARDED_MODULE_RULES_CTOR
    public ViveportSDK(TargetInfo Target)
#else
    public ViveportSDK(ReadOnlyTargetRules Target) : base(Target)
#endif
    {
        PublicIncludePaths.AddRange(
            new string[] {
                "ViveportSDK/Public"
                // ... add public include paths required here ...
            }
        );
        PrivateIncludePaths.AddRange(
            new string[] {
                "ViveportSDK/Private",
                Path.Combine(ThirdPartyPath, "Viveport", "Includes"),
                // ... add other private include paths required here ...
            }
        );

        PublicIncludePathModuleNames.Add("Launch");

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "UMG",
                // ... add other public dependencies that you statically link with here ...
            }
        );
        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Json",
                "JsonUtilities"
                // ... add private dependencies that you statically link with here ...    
            }
        );
        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
                // ... add any modules that your module loads dynamically here ...
            }
        );

        LoadViveportLibrary(Target);
    }

#if !WITH_FORWARDED_MODULE_RULES_CTOR
    public bool LoadViveportLibrary(TargetInfo Target)
#else
    public bool LoadViveportLibrary(ReadOnlyTargetRules Target)
#endif
    {
        bool isLibrarySupported = false;

        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
            isLibrarySupported = true;
            string platformString = Target.Platform == UnrealTargetPlatform.Win64 ? "Win64" : "Win32";
            platformString = Path.Combine("Libraries", platformString);
            string LibrariesPath = Path.Combine(ThirdPartyPath, "Viveport", platformString);

            PublicLibraryPaths.Add(LibrariesPath);
            if (Target.Platform == UnrealTargetPlatform.Win64)
            {
                PublicAdditionalLibraries.Add("viveport_api64.lib");
            }
            else
            {
                PublicAdditionalLibraries.Add("viveport_api.lib");
            }
            PublicAdditionalLibraries.Add("viveport_ext_api.lib");
            PublicLibraryPaths.Add(LibrariesPath);
            if (Target.Platform == UnrealTargetPlatform.Win64)
            {
                PublicDelayLoadDLLs.Add("viveport_api64.dll");
            }
            else
            {
                PublicDelayLoadDLLs.Add("viveport_api.dll");
            }
            
            PublicDelayLoadDLLs.Add("viveport_ext_api.dll");
            if (Target.Platform == UnrealTargetPlatform.Win64)
            {
                RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(LibrariesPath, "viveport_api64.dll")));
            }
            else
            {
                RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(LibrariesPath, "viveport_api.dll")));
            }
            RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(LibrariesPath, "viveport_ext_api.dll")));
        }
        else if (Target.Platform == UnrealTargetPlatform.Android)
        {
#if !WITH_FORWARDED_MODULE_RULES_CTOR
            string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, BuildConfiguration.RelativeEnginePath);
#else
            string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
#endif
            System.Console.WriteLine("_______________________ Path " + PluginPath);
            AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", Path.Combine(PluginPath, "ViveportSDK_APL.xml")));
            PublicAdditionalLibraries.Add(ThirdPartyPath + "Viveport/jniLibs/armeabi-v7a/libViveportSdkJni.so");
        }

        if (isLibrarySupported)
        {
            // Include path
            PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "Viveport", "Includes"));
        }

        Definitions.Add(string.Format("WITH_VIVEPORTSDK_BINDING={0}", isLibrarySupported ? 1 : 0));

        return isLibrarySupported;
    }
}
