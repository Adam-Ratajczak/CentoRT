#include "GenCppBridgeImpl.hpp"
#include <iostream>

bool GenCppBridgeImpl::Execute() const {
	return true;
}

void GenCppBridgeImpl::Dump() const {
	std::cout << "=== GenCppBridgeImpl ===\n";
	std::cout << "bridge: " << _bridge << "\n";
	std::cout << "outputDir: " << _outputDir << "\n";
}
