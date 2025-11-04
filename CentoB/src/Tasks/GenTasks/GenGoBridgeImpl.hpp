#pragma once
#include "../ITask.hpp"

class GenGoBridgeImpl : public ITask {
public:
	GenGoBridgeImpl(const std::filesystem::path& bridge, const std::filesystem::path& outputDir)
		: _bridge{ bridge }
		, _outputDir{ outputDir }{ }

	bool Execute() const override;
	void Dump() const override;
	EOrder GetOrder() const override { return EOrder::GEN; }

private:
	std::filesystem::path _bridge;
	std::filesystem::path _outputDir;
};
