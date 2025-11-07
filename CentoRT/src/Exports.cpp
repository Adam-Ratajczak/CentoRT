#include <CentoCommon.hpp>
#include <iostream>

CENTO_API void Initialize()
{
    std::cout << "[CentoRT] Initialized.\n";
}

CENTO_API void Shutdown()
{
    std::cout << "[CentoRT] Shutdown.\n";
}

CENTO_API void LoadModule(_cento_string_def* identifier) {
    std::string id(identifier->cData, identifier->cSize);
}

CENTO_API void UnloadModule(_cento_string_def* identifier) {
    std::string id(identifier->cData, identifier->cSize);
}
