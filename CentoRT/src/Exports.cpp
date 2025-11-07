#include <Export.hpp>
#include <iostream>

CENTO_API void Initialize()
{
    std::cout << "[CentoRT] Initialized.\n";
}

CENTO_API void Shutdown()
{
    std::cout << "[CentoRT] Shutdown.\n";
}

CENTO_API void LoadModule(size_t hash) {
    std::cout << "[CentoRT] Module loaded: " << hash << "\n";
}

CENTO_API void UnloadModule(size_t hash) {
    std::cout << "[CentoRT] Module unloaded: " << hash << "\n";
}
