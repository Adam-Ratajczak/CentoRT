#include "BuildNinjaTask.hpp"
#include <iostream>

bool BuildNinjaTask::Execute() const {
	return true;
}

void BuildNinjaTask::Dump() const {
	std::cout << "=== BuildNinjaTask ===\n";
	std::cout << "ninjaDir: " << _ninjaDir << "\n";
	std::cout << "outdir: " << _outdir << "\n";
}
