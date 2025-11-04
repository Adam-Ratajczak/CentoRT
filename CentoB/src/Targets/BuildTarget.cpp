#include "BuildTarget.hpp"
#include <iostream>

BuildTarget::BuildTarget(const ManifestObjects::ManifestTarget& target) {
	_name = target.name.has_value() ? *target.name : "";
	std::filesystem::path path = Utils::NormalizePath(target.path.has_value() ? *target.path : "");
	if (target.sources.has_value()) {
		for (const auto& pattern : *target.sources) {
			std::vector<std::filesystem::path> paths;
			Utils::ExpandGlob(pattern, path, paths);
			_sources.insert(_sources.end(), paths.begin(), paths.end());
		}
	}

	if (target.compilerOptions.has_value()) {
		_compilerOptions = *target.compilerOptions;
	}

	if (target.linkerOptions.has_value()) {
		_linkerOptions = *target.linkerOptions;
	}

	if (target.intDir.has_value()) {
		_intDir = *target.intDir;
	}

	if (_intDir.empty()) {
		_intDir = path / "int";
	}
	_intDir = Utils::NormalizePath(_intDir);

	if (target.outDir.has_value()) {
		_outDir = *target.outDir;
	}

	if (_outDir.empty()) {
		_outDir = path / "out";
	}
	_outDir = Utils::NormalizePath(_outDir);

	if (target.bridges.has_value() && target.bridges->implements.has_value()) {
		for (const auto& pattern : *target.bridges->implements) {
			std::vector<std::filesystem::path> paths;
			Utils::ExpandGlob(pattern, path, paths);
			_bridgesImplements.insert(_bridgesImplements.end(), paths.begin(), paths.end());
		}
	}

	if (target.bridges.has_value() && target.bridges->uses.has_value()) {
		for (const auto& pattern : *target.bridges->uses) {
			std::vector<std::filesystem::path> paths;
			Utils::ExpandGlob(pattern, path, paths);
			_bridgesUses.insert(_bridgesUses.end(), paths.begin(), paths.end());
		}
	}
}

void BuildTarget::Dump() const {
	auto dumpVec = [](const auto& vec) {
		std::cout << "[";
		bool first = true;
		for (const auto& path : vec) {
			if (!first) {
				std::cout << ",";
			}
			std::cout << path;
			first = false;
		}
		std::cout << "]\n";
		};
	std::cout << "name: " << _name << "\n";
	std::cout << "sources: "; dumpVec(_sources);
	std::cout << "compilerOptions: "; dumpVec(_compilerOptions);
	std::cout << "linkerOptions: "; dumpVec(_linkerOptions);
	std::cout << "intDir: " << _intDir << "\n";
	std::cout << "outDir: " << _outDir << "\n";
	std::cout << "bridgesImplements: "; dumpVec(_bridgesImplements);
	std::cout << "bridgesUses: "; dumpVec(_bridgesUses);
}
