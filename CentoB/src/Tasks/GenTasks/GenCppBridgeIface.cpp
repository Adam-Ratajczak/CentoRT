#include "GenCppBridgeIface.hpp"
#include <iostream>

bool GenCppBridgeIface::Execute() const {
	return true;
}

void GenCppBridgeIface::Dump() const {
	std::cout << "=== GenCppBridgeIface ===\n";
	std::cout << "bridge: " << _bridge << "\n";
	std::cout << "outputDir: " << _outputDir << "\n";
}
