#include <iostream>
#include "Export.h"

extern "C" {
    LIB1_API void cento_initialize()
    {
        std::cout << "[Lib1] Initialized.\n";
    }

    LIB1_API void cento_shutdown()
    {
        std::cout << "[Lib1] Shutdown.\n";
    }
}
