#include "GenGoBridgeIface.hpp"
#include <iostream>

bool GenGoBridgeIface::Execute() const {
	return true;
}

void GenGoBridgeIface::Dump() const {
	std::cout << "=== GenGoBridgeIface ===\n";
	std::cout << "bridge: " << _bridge << "\n";
	std::cout << "outputDir: " << _outputDir << "\n";
}
