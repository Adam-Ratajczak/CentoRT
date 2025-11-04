#include "GoGoTarget.hpp"
#include <iostream>

#include <Tasks/GenTasks/GenGoBridgeImpl.hpp>
#include <Tasks/GenTasks/GenGoBridgeIface.hpp>
#include <Tasks/GenTasks/GenGoTask.hpp>
#include <Tasks/BuildTasks/BuildGoTask.hpp>

std::string GoGoTarget::StaticClassName = "go:go";

GoGoTarget::GoGoTarget(const ManifestObjects::ManifestTarget& target) : BuildTarget(target) {

}

void GoGoTarget::Dump() const {
	std::cout << "=== " << StaticClassName << " ===\n";
	BuildTarget::Dump();
}

void GoGoTarget::FetchTasks(std::vector<std::unique_ptr<ITask>>& tasks) const {
	std::vector<std::filesystem::path> sources = _sources;
	for (const auto& bridge : _bridgesImplements) {
		auto genDir = _intDir / "generated" / "impl/";
		auto bridgeFileName = bridge.filename().string();
		auto bridgeName = bridgeFileName.substr(0, bridgeFileName.rfind("."));
		auto sourceBridgeFile = Utils::NormalizePath(genDir / (bridgeName + ".go"));

		if (std::find(sources.begin(), sources.end(), sourceBridgeFile) == sources.end()) {
			sources.emplace_back(sourceBridgeFile);
			tasks.emplace_back(std::make_unique<GenGoBridgeImpl>(bridge, sourceBridgeFile));
		}
	}

	for (const auto& bridge : _bridgesUses) {
		auto genDir = _intDir / "generated/iface/";
		auto bridgeFileName = bridge.filename().string();
		auto bridgeName = bridgeFileName.substr(0, bridgeFileName.rfind("."));
		auto sourceBridgeFile = Utils::NormalizePath(genDir / (bridgeName + ".go"));

		if (std::find(sources.begin(), sources.end(), sourceBridgeFile) == sources.end()) {
			sources.emplace_back(sourceBridgeFile);
			tasks.emplace_back(std::make_unique<GenGoBridgeIface>(bridge, sourceBridgeFile));
		}
	}

	tasks.emplace_back(std::make_unique<GenGoTask>(sources, _compilerOptions));
	tasks.emplace_back(std::make_unique<BuildGoTask>(_intDir, _intDir, _outDir));
}
