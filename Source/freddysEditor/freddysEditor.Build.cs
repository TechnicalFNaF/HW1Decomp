using UnrealBuildTool;

public class freddysEditor : ModuleRules 
{
	public freddysEditor(ReadOnlyTargetRules Target) : base(Target) 
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(new string[] 
		{
			"Core",
			"CoreUObject",
			"Engine",
			"PakFile",
			"AssetRegistry",
			"ContentBrowser",
		});
	}
}
