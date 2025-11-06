#pragma once
#include "../ITask.hpp"

class GenGoTask : public ITask {
public:
	GenGoTask(const std::filesystem::path& intdir, const std::vector<std::filesystem::path>& sources, const std::string& name, const std::string& version, const std::string& buildmode, const std::vector<std::string>& compilerOptions, const std::vector<std::string>& linkerOptions)
		: _intdir{ intdir }
		, _sources{ sources }
		, _name{ name }
		, _version{ version }
		, _buildmode{ buildmode }
		, _compilerOptions{ compilerOptions }
		, _linkerOptions{ linkerOptions } { }

	bool Execute() const override;
	void Dump() const override;
	EOrder GetOrder() const override { return EOrder::POSTGEN; }

private:
	std::filesystem::path _intdir;
	std::vector<std::filesystem::path> _sources;
	std::string _name;
	std::string _version;
	std::string _buildmode;
	std::vector<std::string> _compilerOptions;
	std::vector<std::string> _linkerOptions;
};
