#include "GenCppBridgeIface.hpp"
#include <iostream>

void GenCppBridgeIface::Execute() const {

}

void GenCppBridgeIface::Dump() const {
	std::cout << "=== GenCppBridgeIface ===\n";
	std::cout << "bridge: " << _bridge << "\n";
	std::cout << "outputDir: " << _outputDir << "\n";
}
