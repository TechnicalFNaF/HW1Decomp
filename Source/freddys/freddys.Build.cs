using UnrealBuildTool;

public class freddys : ModuleRules {
	public freddys(ReadOnlyTargetRules Target) : base(Target) {
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"UMG",
			"ViveportSDK",
			"MoviePlayer",
		});
	}
}
