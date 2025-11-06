#include "RsCargoTarget.hpp"
#include <iostream>

#include <Tasks/GenTasks/GenRsBridgeImpl.hpp>
#include <Tasks/GenTasks/GenRsBridgeIface.hpp>
#include <Tasks/GenTasks/GenCargoTask.hpp>
#include <Tasks/BuildTasks/BuildCargoTask.hpp>

std::string RsCargoTarget::StaticClassName = "rs:cargo";

RsCargoTarget::RsCargoTarget(const ManifestObjects::ManifestTarget& target) : BuildTarget(target) {

}

void RsCargoTarget::Dump() const {
	std::cout << "=== " << StaticClassName << " ===\n";
	BuildTarget::Dump();
}

void RsCargoTarget::FetchTasks(std::vector<std::unique_ptr<ITask>>& tasks) const {
	std::vector<std::filesystem::path> sources = _sources;
	for (const auto& bridge : _bridgesImplements) {
		auto genDir = _intDir / "generated" / "impl/";
		auto bridgeFileName = bridge.filename().string();
		auto bridgeName = bridgeFileName.substr(0, bridgeFileName.rfind("."));
		auto sourceBridgeFile = Utils::NormalizePath(genDir / (bridgeName + ".rs"));

		if (std::find(sources.begin(), sources.end(), sourceBridgeFile) == sources.end()) {
			sources.emplace_back(sourceBridgeFile);
			tasks.emplace_back(std::make_unique<GenRsBridgeImpl>(bridge, sourceBridgeFile));
		}
	}

	for (const auto& bridge : _bridgesUses) {
		auto genDir = _intDir / "generated/iface/";
		auto bridgeFileName = bridge.filename().string();
		auto bridgeName = bridgeFileName.substr(0, bridgeFileName.rfind("."));
		auto sourceBridgeFile = Utils::NormalizePath(genDir / (bridgeName + ".rs"));

		if (std::find(sources.begin(), sources.end(), sourceBridgeFile) == sources.end()) {
			sources.emplace_back(sourceBridgeFile);
			tasks.emplace_back(std::make_unique<GenRsBridgeIface>(bridge, sourceBridgeFile));
		}
	}
	auto options = _compilerOptions;
	options.insert(options.end(), _linkerOptions.begin(), _linkerOptions.end());

	std::vector<std::string> crateType;
	if (_type == "lib") {
		crateType.emplace_back("staticlib");
	}else if (_type == "dylib") {
		crateType.emplace_back("dylib");
	}
	
	tasks.emplace_back(std::make_unique<GenCargoTask>(_intDir, sources, _name, "0.1.0", _standard, crateType, options));
	tasks.emplace_back(std::make_unique<BuildCargoTask>(_intDir, _intDir, _outDir));
}
