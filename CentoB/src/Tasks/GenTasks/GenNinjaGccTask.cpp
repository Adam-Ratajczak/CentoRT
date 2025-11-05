#include "GenNinjaGccTask.hpp"
#include <iostream>
#include <Generators/NinjaGenerator.hpp>

bool GenNinjaGccTask::Execute() const {
	std::filesystem::create_directories(_intdir);
	
	NinjaGenerator generator;
	generator.Init(_name, "gcc", _sources, _compilerOptions, _linkerOptions, _staticlib);

	return generator.SaveToFile(_intdir / "build.ninja");
}

void GenNinjaGccTask::Dump() const {
	std::cout << "=== GenNinjaGccTask ===\n";

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
	std::cout << "intdir: " << _intdir << "\n";
	std::cout << "sources: "; dumpVec(_sources);
	std::cout << "compilerOptions: "; dumpVec(_compilerOptions);
	std::cout << "linkerOptions: "; dumpVec(_linkerOptions);
	std::cout << "static: " << _staticlib << "\n";
}
