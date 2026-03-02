using UnrealBuildTool;

public class freddysTarget : TargetRules 
{
	public freddysTarget(TargetInfo Target) : base(Target) 
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange(new string[] 
		{
			"freddys",
			"ViveMixedReality",
			"ViveportSDK",
		});
	}
}
