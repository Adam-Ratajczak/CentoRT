#include "GenCsBridgeImpl.hpp"
#include <iostream>

void GenCsBridgeImpl::Execute() const {

}

void GenCsBridgeImpl::Dump() const {
	std::cout << "=== GenCsBridgeImpl ===\n";
	std::cout << "bridge: " << _bridge << "\n";
	std::cout << "outputDir: " << _outputDir << "\n";
}
