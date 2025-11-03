#include "CsDotnetTarget.hpp"
#include <iostream>

#include <Tasks/GenTasks/GenCsBridgeImpl.hpp>
#include <Tasks/GenTasks/GenCsBridgeIface.hpp>
#include <Tasks/GenTasks/GenDotnetTask.hpp>
#include <Tasks/BuildTasks/BuildDotnetTask.hpp>

std::string CsDotnetTarget::StaticClassName = "cs:dotnet";

CsDotnetTarget::CsDotnetTarget(const ManifestObjects::ManifestTarget& target) : BuildTarget(target) {

}

void CsDotnetTarget::Dump() const {
	std::cout << "=== " << StaticClassName << " ===\n";
	BuildTarget::Dump();
}

void CsDotnetTarget::FetchTasks(std::vector<std::unique_ptr<ITask>>& tasks) const {
	std::vector<std::filesystem::path> sources = _sources;
	std::vector<std::filesystem::path> includeDirs = _includeDirs;
	for (const auto& bridge : _bridgesImplements) {
		auto genDir = _intDir / "generated" / "impl";
		auto bridgeName = bridge.string().substr(0, bridge.string().rfind("."));
		tasks.emplace_back(std::make_unique<GenCsBridgeImpl>(bridge, genDir));

		auto sourceBridgeFile = genDir / (bridgeName + ".cs");

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
		tasks.emplace_back(std::make_unique<GenCsBridgeIface>(bridge, genDir));

		auto sourceBridgeFile = genDir / (bridgeName + ".cs");

		if (std::find(_sources.begin(), _sources.end(), sourceBridgeFile) == _sources.end()) {
			sources.emplace_back(sourceBridgeFile);
		}

		if (std::find(_includeDirs.begin(), _includeDirs.end(), genDir) == _includeDirs.end()) {
			includeDirs.emplace_back(genDir);
		}
	}

	tasks.emplace_back(std::make_unique<GenDotnetTask>(sources, includeDirs, _compilerOptions));
	tasks.emplace_back(std::make_unique<BuildDotnetTask>(_intDir, _intDir, _outDir));
}
