#pragma once
#include "../ITask.hpp"

class GenDotnetTask : public ITask {
public:
	GenDotnetTask(const std::vector<std::filesystem::path>& sources, const std::vector<std::filesystem::path>& includeDirs, const std::vector<std::string>& compilerOptions)
		: _sources{ sources }
		, _includeDirs{ includeDirs }
		, _compilerOptions{ compilerOptions } { }

	void Execute() const override;
	void Dump() const override;
	EOrder GetOrder() const override { return EOrder::GEN; }

private:
	std::vector<std::filesystem::path> _sources;
	std::vector<std::filesystem::path> _includeDirs;
	std::vector<std::string> _compilerOptions;
};
