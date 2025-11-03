#include "GenRsBridgeIface.hpp"
#include <iostream>

void GenRsBridgeIface::Execute() const {

}

void GenRsBridgeIface::Dump() const {
	std::cout << "=== GenRsBridgeIface ===\n";
	std::cout << "bridge: " << _bridge << "\n";
	std::cout << "outputDir: " << _outputDir << "\n";
}
