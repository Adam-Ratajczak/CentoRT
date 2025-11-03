#include "GenCppBridgeImpl.hpp"
#include <iostream>

void GenCppBridgeImpl::Execute() const {

}

void GenCppBridgeImpl::Dump() const {
	std::cout << "=== GenCppBridgeImpl ===\n";
	std::cout << "bridge: " << _bridge << "\n";
	std::cout << "outputDir: " << _outputDir << "\n";
}
