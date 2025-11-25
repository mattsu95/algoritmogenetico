#pragma once

#include <iostream>

#define DEBUG_MODE

#ifdef DEBUG_MODE
    #define DEBUG_PRINT(x) std::cout << "[DEBUG] " << x << std::endl;
#else
    #define DEBUG_PRINT(x)
#endif
