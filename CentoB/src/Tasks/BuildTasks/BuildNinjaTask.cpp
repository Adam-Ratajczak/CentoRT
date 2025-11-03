#include "BuildNinjaTask.hpp"
#include <iostream>

void BuildNinjaTask::Execute() const {

}

void BuildNinjaTask::Dump() const {
	std::cout << "=== BuildNinjaTask ===\n";
	std::cout << "file: " << _file << "\n";
	std::cout << "intdir: " << _intdir << "\n";
	std::cout << "outdir: " << _outdir << "\n";
}
