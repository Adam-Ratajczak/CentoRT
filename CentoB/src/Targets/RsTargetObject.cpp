#include "RsTargetObject.hpp"
#include <iostream>

RsTargetObject::RsTargetObject(const ManifestTarget& target) {
	auto path = target.path.has_value() ? *target.path : "";
	if (target.sources.has_value()) {
		for (const auto& pattern : *target.sources) {
			std::vector<std::filesystem::path> paths;
			Utils::ExpandGlob(pattern, path, paths);
			_sources.insert(_sources.end(), paths.begin(), paths.end());
		}
	}

	if (target.includeDirs.has_value()) {
		for (const auto& pattern : *target.includeDirs) {
			std::vector<std::filesystem::path> paths;
			Utils::ExpandGlob(pattern, path, paths);
			_includeDirs.insert(_includeDirs.end(), paths.begin(), paths.end());
		}
	}

	if (target.compilerOptions.has_value()) {
		_compilerOptions = *target.compilerOptions;
	}

	if (target.intDir.has_value()) {
		std::vector<std::filesystem::path> paths;
		Utils::ExpandGlob(*target.intDir, path, paths);

		if (!paths.empty()) {
			_intDir = paths[0];
		}
	}

	if (target.outDir.has_value()) {
		std::vector<std::filesystem::path> paths;
		Utils::ExpandGlob(*target.outDir, path, paths);

		if (!paths.empty()) {
			_outDir = paths[0];
		}
	}

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

void RsTargetObject::Dump() const {
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
	std::cout << "sources: "; dumpVec(_sources);
	std::cout << "includeDirs: "; dumpVec(_includeDirs);
	std::cout << "compilerOptions: "; dumpVec(_compilerOptions);
	std::cout << "intDir: " << _intDir << "\n";
	std::cout << "outDir: " << _outDir << "\n";
	std::cout << "bridgesImplements: "; dumpVec(_bridgesImplements);
	std::cout << "bridgesUses: "; dumpVec(_bridgesUses);
}
