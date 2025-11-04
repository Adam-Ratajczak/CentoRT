#pragma once
#include "../ITask.hpp"

class GenCargoTask : public ITask {
public:
	GenCargoTask(const std::vector<std::filesystem::path>& sources, const std::vector<std::string>& compilerOptions)
		: _sources{ sources }
		, _compilerOptions{ compilerOptions } { }

	bool Execute() const override;
	void Dump() const override;
	EOrder GetOrder() const override { return EOrder::POSTGEN; }

private:
	std::vector<std::filesystem::path> _sources;
	std::vector<std::string> _compilerOptions;
};
