#pragma once
#include "../ITask.hpp"

class GenDotnetTask : public ITask {
public:
	GenDotnetTask(const std::filesystem::path& intdir, const std::vector<std::filesystem::path>& sources, const std::vector<std::string>& options)
		: _intdir{ intdir }
		, _sources{ sources }
		, _options{ options } { }

	bool Execute() const override;
	void Dump() const override;
	EOrder GetOrder() const override { return EOrder::POSTGEN; }

private:
	std::filesystem::path _intdir;
	std::vector<std::filesystem::path> _sources;
	std::vector<std::string> _options;
};
