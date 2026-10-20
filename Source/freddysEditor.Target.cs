﻿using UnrealBuildTool;

public class freddysEditorTarget : TargetRules 
{
	public freddysEditorTarget(TargetInfo Target) : base(Target) 
	{
		Type = TargetType.Editor;
		
		if (Target.Platform == UnrealTargetPlatform.Win32
		    || Target.Platform == UnrealTargetPlatform.Win64)
		{
			FreddysShared.SetWindowsCompilerRules(this);
		}
		
		ExtraModuleNames.AddRange(new string[] 
		{
			"freddys",
		});
	}
}