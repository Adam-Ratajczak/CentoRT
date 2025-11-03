#include "GenDotnetTask.hpp"
#include <iostream>

void GenDotnetTask::Execute() const {

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

	std::cout << "sources: "; dumpVec(_sources);
	std::cout << "includeDirs: "; dumpVec(_includeDirs);
	std::cout << "compilerOptions: "; dumpVec(_compilerOptions);
}
