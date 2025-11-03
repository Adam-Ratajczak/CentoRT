#include "CppNinjaTarget.hpp"
#include <iostream>

#include <Tasks/GenTasks/GenCppBridgeImpl.hpp>
#include <Tasks/GenTasks/GenCppBridgeIface.hpp>
#include <Tasks/GenTasks/GenNinjaTask.hpp>
#include <Tasks/BuildTasks/BuildNinjaTask.hpp>

std::string CppNinjaTarget::StaticClassName = "cpp:ninja";

CppNinjaTarget::CppNinjaTarget(const ManifestObjects::ManifestTarget& target) : BuildTarget(target) {

}

void CppNinjaTarget::Dump() const {
	std::cout << "=== " << StaticClassName << " ===\n";
	BuildTarget::Dump();
}

void CppNinjaTarget::FetchTasks(std::vector<std::unique_ptr<ITask>>& tasks) const {
	std::vector<std::filesystem::path> sources = _sources;
	std::vector<std::filesystem::path> includeDirs = _includeDirs;
	for (const auto& bridge : _bridgesImplements) {
		auto genDir = _intDir / "generated" / "impl";
		auto bridgeName = bridge.string().substr(0, bridge.string().rfind("."));
		tasks.emplace_back(std::make_unique<GenCppBridgeImpl>(bridge, genDir));

		auto sourceBridgeFile = genDir / (bridgeName + ".cpp");

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
		tasks.emplace_back(std::make_unique<GenCppBridgeIface>(bridge, genDir));

		auto sourceBridgeFile = genDir / (bridgeName + ".cpp");

		if (std::find(_sources.begin(), _sources.end(), sourceBridgeFile) == _sources.end()) {
			sources.emplace_back(sourceBridgeFile);
		}

		if (std::find(_includeDirs.begin(), _includeDirs.end(), genDir) == _includeDirs.end()) {
			includeDirs.emplace_back(genDir);
		}
	}

	tasks.emplace_back(std::make_unique<GenNinjaTask>(sources, includeDirs, _compilerOptions));
	tasks.emplace_back(std::make_unique<BuildNinjaTask>(_intDir, _intDir, _outDir));
}
