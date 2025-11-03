#include "GenGoBridgeIface.hpp"
#include <iostream>

void GenGoBridgeIface::Execute() const {

}

void GenGoBridgeIface::Dump() const {
	std::cout << "=== GenGoBridgeIface ===\n";
	std::cout << "bridge: " << _bridge << "\n";
	std::cout << "outputDir: " << _outputDir << "\n";
}
