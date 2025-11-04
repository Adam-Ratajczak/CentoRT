#pragma once
#include "../ITask.hpp"

class GenNinjaGccTask : public ITask {
public:
	GenNinjaGccTask(const std::filesystem::path& intdir, const std::vector<std::filesystem::path>& sources, const std::vector<std::string>& compilerOptions, const std::vector<std::string>& linkerOptions, const std::string& name)
		: _intdir{ intdir }
		, _sources{ sources }
		, _compilerOptions{ compilerOptions }
		, _linkerOptions{ linkerOptions }
		, _name{ name } { }

	bool Execute() const override;
	void Dump() const override;
	EOrder GetOrder() const override { return EOrder::POSTGEN; }

private:
	std::filesystem::path _intdir;
	std::vector<std::filesystem::path> _sources;
	std::vector<std::string> _compilerOptions;
	std::vector<std::string> _linkerOptions;
	std::string _name;
};
