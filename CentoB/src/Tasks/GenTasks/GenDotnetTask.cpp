#include "GenDotnetTask.hpp"
#include <iostream>

bool GenDotnetTask::Execute() const {
	return true;
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
	std::cout << "compilerOptions: "; dumpVec(_compilerOptions);
}
