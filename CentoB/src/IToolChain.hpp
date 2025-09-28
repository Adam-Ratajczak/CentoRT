#pragma once
#include <string>
#include <vector>
#include <filesystem>

struct CompilerData {
	std::string Name;
	std::string Type;

	std::vector<std::filesystem::path> Sources;
	std::vector<std::filesystem::path> IncludeDirs;
	std::vector<std::string> LinkAganist;

	std::filesystem::path IntermediateDir;
	std::filesystem::path OutputDir;
};

class IToolChain {
	virtual bool Execute(const CompilerData& data, std::string& errMsg) = 0;
};
