using UnrealBuildTool;

public class freddysGameTarget : TargetRules {
	public freddysGameTarget(TargetInfo Target) : base(Target) {
		Type = TargetType.Game;
		ExtraModuleNames.AddRange(new string[] {
			"freddys",
			"ViveMixedReality",
			"ViveportSDK",
		});
	}
}
