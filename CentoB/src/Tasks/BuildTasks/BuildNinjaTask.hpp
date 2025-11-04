#pragma once
#include "../ITask.hpp"

class BuildNinjaTask : public ITask {
public:
	BuildNinjaTask(const std::filesystem::path& ninjaDir, const std::filesystem::path& outdir)
		: _ninjaDir{ ninjaDir }
		, _outdir{ outdir } { }

	bool Execute() const override;
	void Dump() const override;
	EOrder GetOrder() const override { return EOrder::BUILD; }

private:
	std::filesystem::path _ninjaDir;
	std::filesystem::path _outdir;
};
