#pragma once
#include "../ITask.hpp"

class BuildGoTask : public ITask {
public:
	BuildGoTask(const std::filesystem::path& file, const std::filesystem::path& intdir, const std::filesystem::path& outdir)
		: _file{ file }
		, _intdir{ intdir }
		, _outdir{ outdir } { }

	bool Execute() const override;
	void Dump() const override;
	EOrder GetOrder() const override { return EOrder::BUILD; }

private:
	std::filesystem::path _file;
	std::filesystem::path _intdir;
	std::filesystem::path _outdir;
};
