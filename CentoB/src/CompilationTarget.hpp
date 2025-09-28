#pragma once
#include "IToolChain.hpp"
#include <string>
#include <vector>
#include <filesystem>
#include <memory>

class CompilationTarget {
	std::string _name;
	std::string _type;

	std::vector<std::filesystem::path> _sources;
	std::vector<std::filesystem::path> _includeDirs;
	std::vector<std::string> _linkAganist;

	std::filesystem::path _intermediateDir;
	std::filesystem::path _outputDir;

	std::weak_ptr<IToolChain> _toolchain;
public:
	void Clean();
	void Make();
};
