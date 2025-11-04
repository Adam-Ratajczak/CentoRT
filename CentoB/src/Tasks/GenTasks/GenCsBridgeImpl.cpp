#include "GenCsBridgeImpl.hpp"
#include <iostream>

bool GenCsBridgeImpl::Execute() const {
	return true;
}

void GenCsBridgeImpl::Dump() const {
	std::cout << "=== GenCsBridgeImpl ===\n";
	std::cout << "bridge: " << _bridge << "\n";
	std::cout << "outputDir: " << _outputDir << "\n";
}
