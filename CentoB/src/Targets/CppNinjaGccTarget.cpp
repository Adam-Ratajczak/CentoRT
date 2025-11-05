#include "CppNinjaGccTarget.hpp"
#include <iostream>

#include <Tasks/GenTasks/GenCppBridgeImpl.hpp>
#include <Tasks/GenTasks/GenCppBridgeIface.hpp>
#include <Tasks/GenTasks/GenNinjaGccTask.hpp>
#include <Tasks/BuildTasks/BuildNinjaTask.hpp>

std::string CppNinjaGccTarget::StaticClassName = "cpp:ninja-gcc";

CppNinjaGccTarget::CppNinjaGccTarget(const ManifestObjects::ManifestTarget& target) : BuildTarget(target) {

}

void CppNinjaGccTarget::Dump() const {
	std::cout << "=== " << StaticClassName << " ===\n";
	BuildTarget::Dump();
}

void CppNinjaGccTarget::FetchTasks(std::vector<std::unique_ptr<ITask>>& tasks) const {
	std::vector<std::filesystem::path> sources = _sources;
	std::vector<std::filesystem::path> includeDirs;
	for (const auto& bridge : _bridgesImplements) {
		auto genDir = _intDir / "generated" / "impl/";
		auto bridgeFileName = bridge.filename().string();
		auto bridgeName = bridgeFileName.substr(0, bridgeFileName.rfind("."));
		auto sourceBridgeFile = Utils::NormalizePath(genDir / (bridgeName + ".cpp"));

		if (std::find(sources.begin(), sources.end(), sourceBridgeFile) == sources.end()) {
			sources.emplace_back(sourceBridgeFile);
			tasks.emplace_back(std::make_unique<GenCppBridgeImpl>(bridge, sourceBridgeFile));
		}

		if (std::find(includeDirs.begin(), includeDirs.end(), genDir) == includeDirs.end()) {
			includeDirs.emplace_back(genDir);
		}
	}

	for (const auto& bridge : _bridgesUses) {
		auto genDir = _intDir / "generated/iface/";
		auto bridgeFileName = bridge.filename().string();
		auto bridgeName = bridgeFileName.substr(0, bridgeFileName.rfind("."));
		auto sourceBridgeFile = Utils::NormalizePath(genDir / (bridgeName + ".cpp"));

		if (std::find(sources.begin(), sources.end(), sourceBridgeFile) == sources.end()) {
			sources.emplace_back(sourceBridgeFile);
			tasks.emplace_back(std::make_unique<GenCppBridgeIface>(bridge, sourceBridgeFile));
		}

		if (std::find(includeDirs.begin(), includeDirs.end(), genDir) == includeDirs.end()) {
			includeDirs.emplace_back(genDir);
		}
	}

	auto compilerOptions = _compilerOptions;
	for (const auto& include : includeDirs) {
		compilerOptions.emplace_back("-I \"" + include.string() + "\"");
	}
	if (!_standard.empty()) {
		compilerOptions.emplace_back("-std=" + _standard);
	}
	auto linkerOptions = _linkerOptions;
	bool staticlib = false;
	if (_type == "dylib") {
		linkerOptions.emplace_back("--shared");
	}
	else if (_type == "lib") {
		staticlib = true;
	}

	tasks.emplace_back(std::make_unique<GenNinjaGccTask>(_name, _intDir, sources, compilerOptions, linkerOptions, staticlib));
	tasks.emplace_back(std::make_unique<BuildNinjaTask>(_intDir, _outDir));
}
