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
	for (const auto& bridge : _bridgesImplements) {
		auto genDir = _intDir / "generated" / "impl/";
		auto bridgeFileName = bridge.filename().string();
		auto bridgeName = bridgeFileName.substr(0, bridgeFileName.rfind("."));
		auto sourceBridgeFile = Utils::NormalizePath(genDir / (bridgeName + ".cs"));

		if (std::find(sources.begin(), sources.end(), sourceBridgeFile) == sources.end()) {
			sources.emplace_back(sourceBridgeFile);
			tasks.emplace_back(std::make_unique<GenCsBridgeImpl>(bridge, sourceBridgeFile));
		}
	}

	for (const auto& bridge : _bridgesUses) {
		auto genDir = _intDir / "generated/iface/";
		auto bridgeFileName = bridge.filename().string();
		auto bridgeName = bridgeFileName.substr(0, bridgeFileName.rfind("."));
		auto sourceBridgeFile = Utils::NormalizePath(genDir / (bridgeName + ".cs"));

		if (std::find(sources.begin(), sources.end(), sourceBridgeFile) == sources.end()) {
			sources.emplace_back(sourceBridgeFile);
			tasks.emplace_back(std::make_unique<GenCsBridgeIface>(bridge, sourceBridgeFile));
		}
	}

	tasks.emplace_back(std::make_unique<GenDotnetTask>(sources, _compilerOptions));
	tasks.emplace_back(std::make_unique<BuildDotnetTask>(_intDir, _intDir, _outDir));
}
