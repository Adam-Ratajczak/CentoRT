#include "GenGoBridgeImpl.hpp"
#include <iostream>

bool GenGoBridgeImpl::Execute() const {
	return true;
}

void GenGoBridgeImpl::Dump() const {
	std::cout << "=== GenGoBridgeImpl ===\n";
	std::cout << "bridge: " << _bridge << "\n";
	std::cout << "outputDir: " << _outputDir << "\n";
}
