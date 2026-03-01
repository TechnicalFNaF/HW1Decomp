using UnrealBuildTool;

public class freddysEditorTarget : TargetRules {
	public freddysEditorTarget(TargetInfo Target) : base(Target) {
		Type = TargetType.Editor;
		ExtraModuleNames.AddRange(new string[] {
			"freddys",
			"ViveMixedReality",
			"ViveportSDK",
		});
	}
}
