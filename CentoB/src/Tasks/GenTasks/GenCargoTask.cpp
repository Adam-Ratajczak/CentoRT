#include "GenCargoTask.hpp"
#include <Generators/CargoGenerator.hpp>
#include <iostream>

bool GenCargoTask::Execute() const {
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

	CargoGenerator generator;
	generator.Init(_name, _version, _edition, _crateType, _options);

	return generator.SaveToFile(_intdir / "Cargo.toml");
}

void GenCargoTask::Dump() const {
	std::cout << "=== GenCargoTask ===\n";

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
	std::cout << "edition: " << _edition << "\n";
	std::cout << "crateType: "; dumpVec(_crateType);
	std::cout << "options: "; dumpVec(_options);
}
