#pragma once
#include "../ITask.hpp"

class BuildDotnetTask : public ITask {
public:
	BuildDotnetTask(const std::filesystem::path& file, const std::filesystem::path& intdir, const std::filesystem::path& outdir)
		: _file{ file }
		, _intdir{ intdir }
		, _outdir{ outdir } { }

	void Execute() const override;
	void Dump() const override;
	EOrder GetOrder() const override { return EOrder::BUILD; }

private:
	std::filesystem::path _file;
	std::filesystem::path _intdir;
	std::filesystem::path _outdir;
};
