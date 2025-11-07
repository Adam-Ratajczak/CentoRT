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

CENTO_API void LoadModule(int hash) {
    std::cout << "[CentoRT] Module loaded: " << hash << "\n";
}

CENTO_API void UnloadModule(int hash) {
    std::cout << "[CentoRT] Module unloaded: " << hash << "\n";
}
