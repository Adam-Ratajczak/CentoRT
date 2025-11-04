#include "BuildCargoTask.hpp"
#include <iostream>

bool BuildCargoTask::Execute() const {
	return true;
}

void BuildCargoTask::Dump() const {
	std::cout << "=== BuildCargoTask ===\n";
	std::cout << "file: " << _file << "\n";
	std::cout << "intdir: " << _intdir << "\n";
	std::cout << "outdir: " << _outdir << "\n";
}
