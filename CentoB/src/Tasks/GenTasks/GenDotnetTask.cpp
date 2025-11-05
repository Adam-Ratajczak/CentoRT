#include "GenDotnetTask.hpp"
#include <Generators/DotnetGenerator.hpp>
#include <iostream>

bool GenDotnetTask::Execute() const {
	std::filesystem::create_directories(_intdir);

	DotnetGenerator generator;
	generator.Init(_sources, _options);

	return generator.SaveToFile(_intdir / "project.csproj");
}

void GenDotnetTask::Dump() const {
	std::cout << "=== GenDotnetTask ===\n";

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

	std::cout << _intdir << "\n";
	std::cout << "sources: "; dumpVec(_sources);
	std::cout << "options: "; dumpVec(_options);
}
