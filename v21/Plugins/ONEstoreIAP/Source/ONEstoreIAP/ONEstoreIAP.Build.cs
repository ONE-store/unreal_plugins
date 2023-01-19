// Some copyright should be here...

using UnrealBuildTool;
using System.IO;

public class ONEstoreIAP : ModuleRules
{
	public ONEstoreIAP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{                
                "CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",

				// ... add private dependencies that you statically link with here ...	
            }
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

		if (Target.Platform == UnrealTargetPlatform.Android){
            string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
            AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginPath, "ONEstoreIAP.UPL.xml"));

            string SDKPath = Path.Combine(ModuleDirectory, "ONEstoreNativeIapHelper");
            string LibraryPath = Path.Combine(SDKPath, "libs");
            string IncludePath = Path.Combine(SDKPath, "include");

            PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "armeabi-v7a",  "libONEstoreNativeIapHelper.so"));
            PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "arm64-v8a",    "libONEstoreNativeIapHelper.so"));
            PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "x86",          "libONEstoreNativeIapHelper.so"));
            PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "x86_64",       "libONEstoreNativeIapHelper.so"));

            PublicIncludePaths.Add(IncludePath);

            PrivateDependencyModuleNames.Add("Launch");
        }	
	}
}
