#include "GenRsBridgeImpl.hpp"
#include <iostream>

bool GenRsBridgeImpl::Execute() const {
	return true;
}

void GenRsBridgeImpl::Dump() const {
	std::cout << "=== GenRsBridgeImpl ===\n";
	std::cout << "bridge: " << _bridge << "\n";
	std::cout << "outputDir: " << _outputDir << "\n";
}
