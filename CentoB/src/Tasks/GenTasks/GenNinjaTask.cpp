#include "GenNinjaTask.hpp"
#include <iostream>

void GenNinjaTask::Execute() const {

}

void GenNinjaTask::Dump() const {
	std::cout << "=== GenNinjaTask ===\n";

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
}
