#include "BuildDotnetTask.hpp"
#include <iostream>

void BuildDotnetTask::Execute() const {

}

void BuildDotnetTask::Dump() const {
	std::cout << "=== BuildDotnetTask ===\n";
	std::cout << "file: " << _file << "\n";
	std::cout << "intdir: " << _intdir << "\n";
	std::cout << "outdir: " << _outdir << "\n";
}
