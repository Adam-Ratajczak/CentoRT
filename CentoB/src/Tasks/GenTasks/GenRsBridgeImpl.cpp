#include "GenRsBridgeImpl.hpp"
#include <iostream>

void GenRsBridgeImpl::Execute() const {

}

void GenRsBridgeImpl::Dump() const {
	std::cout << "=== GenRsBridgeImpl ===\n";
	std::cout << "bridge: " << _bridge << "\n";
	std::cout << "outputDir: " << _outputDir << "\n";
}
