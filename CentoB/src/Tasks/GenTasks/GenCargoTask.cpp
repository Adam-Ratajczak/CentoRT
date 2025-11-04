#include "GenCargoTask.hpp"
#include <iostream>

bool GenCargoTask::Execute() const {
	return true;
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

	std::cout << "sources: "; dumpVec(_sources);
	std::cout << "compilerOptions: "; dumpVec(_compilerOptions);
}
