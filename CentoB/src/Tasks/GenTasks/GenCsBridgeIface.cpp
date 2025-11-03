#include "GenCsBridgeIface.hpp"
#include <iostream>

void GenCsBridgeIface::Execute() const {

}

void GenCsBridgeIface::Dump() const {
	std::cout << "=== GenCsBridgeIface ===\n";
	std::cout << "bridge: " << _bridge << "\n";
	std::cout << "outputDir: " << _outputDir << "\n";
}
