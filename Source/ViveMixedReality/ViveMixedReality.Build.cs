using UnrealBuildTool;

public class ViveMixedReality : ModuleRules {
	public ViveMixedReality(ReadOnlyTargetRules Target) : base(Target) {
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
		});
	}
}
