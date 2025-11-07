#include <iostream>
#include "Export.h"

extern "C" {
    LIB2_API void cento_initialize()
    {
        std::cout << "[Lib2] Initialized.\n";
    }

    LIB2_API void cento_shutdown()
    {
        std::cout << "[Lib2] Shutdown.\n";
    }
}
