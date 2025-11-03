#include "BuildGoTask.hpp"
#include <iostream>

void BuildGoTask::Execute() const {

}

void BuildGoTask::Dump() const {
	std::cout << "=== BuildGoTask ===\n";
	std::cout << "file: " << _file << "\n";
	std::cout << "intdir: " << _intdir << "\n";
	std::cout << "outdir: " << _outdir << "\n";
}
