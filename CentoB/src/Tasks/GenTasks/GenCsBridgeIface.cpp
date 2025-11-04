#include "GenCsBridgeIface.hpp"
#include <iostream>

bool GenCsBridgeIface::Execute() const {
	return true;
}

void GenCsBridgeIface::Dump() const {
	std::cout << "=== GenCsBridgeIface ===\n";
	std::cout << "bridge: " << _bridge << "\n";
	std::cout << "outputDir: " << _outputDir << "\n";
}
