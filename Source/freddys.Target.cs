using System.IO;
using Tools.DotNETCommon;
using UnrealBuildTool;

public static class FreddysShared
{
	public static void SetWindowsCompilerRules(TargetRules Target)
	{
		Target.WindowsPlatform.Compiler = WindowsCompiler.VisualStudio2019;
		UseLatestCompatibleToolset(Target);
	}

	private static string FindVSPath(string Version, bool bIs32Bit = true)
	{
		string ProgramFilesPath = (bIs32Bit ? "Program Files (x86)" : "Program Files");
		string TargetPath = string.Format(@"{0}\Microsoft Visual Studio\{1}\Community\VC\Tools\MSVC\", ProgramFilesPath, Version);

		foreach (var Drive in DriveInfo.GetDrives())
		{
			string DrivePath = Drive.Name + TargetPath;
			Log.TraceInformation("Trying VS in {0}", DrivePath);

			if (Directory.Exists(DrivePath))
			{
				Log.TraceInformation("Found VS in {0}", DrivePath);
				return DrivePath;
			}
		}
		
		return "";
	}

	private static void UseLatestCompatibleToolset(TargetRules Target)
	{
		string MSVCToolsets = FindVSPath("2019", true);
		bool bIs2022 = false;
		
		if (!Directory.Exists(MSVCToolsets))
		{
			MSVCToolsets = FindVSPath("2022", false);
			bIs2022 = true;
		}

		if (Directory.Exists(MSVCToolsets))
		{
			string LatestVersion = "None";
			int CurrentIntVersion = 0;

			foreach (string CurrentDir in Directory.GetDirectories(MSVCToolsets))
			{
				DirectoryInfo CurrentDirInfo = new DirectoryInfo(CurrentDir);
				int FoundIntVersion = int.Parse(CurrentDirInfo.Name.Replace(".", ""));

				if (CurrentIntVersion == 0)
					CurrentIntVersion = FoundIntVersion;
				
				if (!bIs2022)
				{
					if (FoundIntVersion < CurrentIntVersion) 
						continue;
				}
				else
				{
					if (FoundIntVersion > CurrentIntVersion) 
						continue;
				}

				LatestVersion = CurrentDirInfo.Name;
				CurrentIntVersion = FoundIntVersion;
			}
			Log.TraceInformation("Using latest toolset {0}", LatestVersion);

			if (LatestVersion != "None")
			{
				Target.WindowsPlatform.CompilerVersion = LatestVersion;
			}
		}
	}
}

public class freddysTarget : TargetRules 
{
	public freddysTarget(TargetInfo Target) : base(Target) 
	{
		Type = TargetType.Game;

		if (Target.Platform == UnrealTargetPlatform.Win32
			|| Target.Platform == UnrealTargetPlatform.Win64)
		{
			FreddysShared.SetWindowsCompilerRules(this);
		}
		
		ExtraModuleNames.AddRange(new string[] 
		{
			"freddys"
        });
	}
}
