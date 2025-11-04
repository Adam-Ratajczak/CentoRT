#include "GenRsBridgeIface.hpp"
#include <iostream>

bool GenRsBridgeIface::Execute() const {
	return true;
}

void GenRsBridgeIface::Dump() const {
	std::cout << "=== GenRsBridgeIface ===\n";
	std::cout << "bridge: " << _bridge << "\n";
	std::cout << "outputDir: " << _outputDir << "\n";
}
