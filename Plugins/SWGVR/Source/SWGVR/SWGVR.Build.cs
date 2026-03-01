using UnrealBuildTool;

public class SWGVR : ModuleRules {
    public SWGVR(ReadOnlyTargetRules Target) : base(Target) {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        
        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "HeadMountedDisplay",
            "InputCore"
        });
    }
}
