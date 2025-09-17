#include "ArgsResolver.hpp"
#include "Log.hpp"
#include "ManifestFile.hpp"
#include <iostream>
#include <string>
#include <vector>

struct CommandDef {
	std::string Name;
	std::vector<std::string> Args;

	CommandDef() = default;
	CommandDef(const std::string& name, const std::vector<std::string>& args) : Name{ name }, Args{ args } {}
};

void ArgsResolver::resolve(int argc, char* argv[]) {
	std::vector<std::string> args(argv, argv + argc);
	std::vector<CommandDef> optionsToExecute;
	static std::set<std::string> possibleNames = { "dump", "help" };

	if (args.size() <= 2) {
		display_help();
		return;
	}

	std::string path = args[1]; 
	if (!std::filesystem::is_directory(path)) {
		Log::LogError("Provided folder must be directory!");
		return;
	}

	CommandDef currDef;
	for (int i = 2; i < args.size(); i++) {
		if (possibleNames.find(args[i]) != possibleNames.end()) {
			if (!currDef.Name.empty()) {
				optionsToExecute.push_back(currDef);

				currDef.Name.clear();
				currDef.Args.clear();
			}
			currDef.Name = args[i];
		}
		else {
			currDef.Args.push_back(args[i]);
		}
	}

	if (!currDef.Name.empty()) {
		optionsToExecute.push_back(currDef);
	}

	for (const auto& optDef : optionsToExecute) {
		if (optDef.Name == "help") {
			if (optionsToExecute.size() != 1) {
				Log::LogError("Help cannot be used with other options!");
				return;
			}
			if (optDef.Args.size() != 0) {
				Log::LogError("Help doesn't take any arguments!");
				return;
			}
			display_help();
			return;
		}

		if (optDef.Name == "dump") {
			if (optionsToExecute.size() != 1) {
				Log::LogError("Dump cannot be used with other options!");
				return;
			}
			if (optDef.Args.size() != 0) {
				Log::LogError("Dump doesn't take any arguments!");
				return;
			}
			resolve_dump(path);
			return;
		}
	}
}

void ArgsResolver::display_help() {
	Log::LogInfo("### CertoB - help ###");
	Log::LogInfo("certob <path> [option1]  [option2]...");
	Log::LogInfo("Available options:");
	Log::LogInfo("dump:\t\tDumps manifest layout");
	Log::LogInfo("help:\t\tDisplays this text");
}

void ArgsResolver::resolve_dump(const std::filesystem::path& localFolder) {
	std::filesystem::path manifestPath = localFolder / "cento.yaml";
	if (!std::filesystem::exists(manifestPath)) {
		Log::LogError("No cento.yaml file in the specified directory.");
		return;
	}

	ManifestFile manifest;
	manifest.LoadFromFile(manifestPath);
	if (manifest.Fail()) {
		Log::LogError(manifest.GetError());
		return;
	}
}
