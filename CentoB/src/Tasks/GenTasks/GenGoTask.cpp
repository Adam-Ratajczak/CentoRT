#include "GenGoTask.hpp"
#include <iostream>
#include <Generators/GoGenerator.hpp>

bool GenGoTask::Execute() const {
	std::filesystem::create_directories(_intdir);
	std::filesystem::create_directories(_intdir / "src");

	for (const auto& path : _sources) {
		auto newPath = _intdir / "src" / path.filename();
		if (std::filesystem::exists(path)) {
			if (std::filesystem::exists(newPath)) {
				std::filesystem::remove(newPath);
			}
			std::filesystem::copy(path, newPath);
		}
	}


	GoGenerator generator;
	generator.Init(_name, _version, _buildmode, _compilerOptions, _linkerOptions);
	return generator.SaveToFile(_intdir / "go.mod", _intdir / "Makefile");
}

void GenGoTask::Dump() const {
	std::cout << "=== GenGoTask ===\n";

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

	std::cout << "intdir: " << _intdir << "\n";
	std::cout << "sources: "; dumpVec(_sources);
	std::cout << "name: " << _name << "\n";
	std::cout << "version: " << _version << "\n";
	std::cout << "buildmode: " << _buildmode << "\n";
	std::cout << "compilerOptions: "; dumpVec(_compilerOptions);
	std::cout << "linkerOptions: "; dumpVec(_linkerOptions);
}
