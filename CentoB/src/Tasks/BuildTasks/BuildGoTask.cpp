#include "BuildGoTask.hpp"
#include <iostream>

bool BuildGoTask::Execute() const {
	return true;
}

void BuildGoTask::Dump() const {
	std::cout << "=== BuildGoTask ===\n";
	std::cout << "file: " << _file << "\n";
	std::cout << "intdir: " << _intdir << "\n";
	std::cout << "outdir: " << _outdir << "\n";
}
