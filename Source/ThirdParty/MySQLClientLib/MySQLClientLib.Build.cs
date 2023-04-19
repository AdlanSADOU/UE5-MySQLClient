using UnrealBuildTool;
using System.IO;

public class MySQLClientLib : ModuleRules
{
    public MySQLClientLib(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;

        string LibraryPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "lib/"));
        string IncludePath = Path.GetFullPath(Path.Combine(ModuleDirectory, "include/"));

        PublicIncludePaths.Add(IncludePath);

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            // string LibraryName = "MySQL"; // Replace with the actual name of your library without file extension
            string LibraryFile = Path.Combine(LibraryPath, "mysqlclient" + ".lib");
            PublicAdditionalLibraries.Add(LibraryFile);

            //RuntimeDependencies.Add(Path.Combine(LibraryPath, "libmysql.dll"));
            //RuntimeDependencies.Add(Path.Combine(LibraryPath, "libcrypto-1_1-x64.dll"));
            //RuntimeDependencies.Add(Path.Combine(LibraryPath, "libssl-1_1-x64.dll"));

            RuntimeDependencies.Add("$(BinaryOutputDir)/libmysql.dll", Path.Combine(LibraryPath, "libmysql.dll"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/libcrypto-1_1-x64.dll", Path.Combine(LibraryPath, "libcrypto-1_1-x64.dll"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/libssl-1_1-x64.dll", Path.Combine(LibraryPath, "libssl-1_1-x64.dll"));
        }
    }
}