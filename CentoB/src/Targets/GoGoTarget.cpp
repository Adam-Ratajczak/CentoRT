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
	std::vector<std::filesystem::path> includeDirs = _includeDirs;
	for (const auto& bridge : _bridgesImplements) {
		auto genDir = _intDir / "generated" / "impl";
		auto bridgeName = bridge.string().substr(0, bridge.string().rfind("."));
		tasks.emplace_back(std::make_unique<GenGoBridgeImpl>(bridge, genDir));

		auto sourceBridgeFile = genDir / (bridgeName + ".go");

		if (std::find(_sources.begin(), _sources.end(), sourceBridgeFile) == _sources.end()) {
			sources.emplace_back(sourceBridgeFile);
		}

		if (std::find(_includeDirs.begin(), _includeDirs.end(), genDir) == _includeDirs.end()) {
			includeDirs.emplace_back(genDir);
		}
	}

	for (const auto& bridge : _bridgesUses) {
		auto genDir = _intDir / "generated" / "iface";
		auto bridgeName = bridge.string().substr(0, bridge.string().rfind("."));
		tasks.emplace_back(std::make_unique<GenGoBridgeIface>(bridge, genDir));

		auto sourceBridgeFile = genDir / (bridgeName + ".go");

		if (std::find(_sources.begin(), _sources.end(), sourceBridgeFile) == _sources.end()) {
			sources.emplace_back(sourceBridgeFile);
		}

		if (std::find(_includeDirs.begin(), _includeDirs.end(), genDir) == _includeDirs.end()) {
			includeDirs.emplace_back(genDir);
		}
	}

	tasks.emplace_back(std::make_unique<GenGoTask>(sources, includeDirs, _compilerOptions));
	tasks.emplace_back(std::make_unique<BuildGoTask>(_intDir, _intDir, _outDir));
}
