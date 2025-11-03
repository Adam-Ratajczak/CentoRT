#include "GenGoBridgeImpl.hpp"
#include <iostream>

void GenGoBridgeImpl::Execute() const {

}

void GenGoBridgeImpl::Dump() const {
	std::cout << "=== GenGoBridgeImpl ===\n";
	std::cout << "bridge: " << _bridge << "\n";
	std::cout << "outputDir: " << _outputDir << "\n";
}
