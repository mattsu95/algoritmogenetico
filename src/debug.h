#pragma once

#include <iostream>

#define DEBUG_MODE

#ifdef DEBUG_MODE
    #define DEBUG_PRINT(x) std::cout << "[DEBUG] " << x << std::endl;
    #define DEBUG_GEN(gen_ptr) \
        do { \
            int counter = 0; \
            DEBUG_PRINT("==========================GERAÇÃO GERADA==========================") \
            for(const auto& i : gen_ptr->subjects){ \
                DEBUG_PRINT("INDIVIDUO " << counter); \
                DEBUG_PRINT("X: " << i.gen_x); \
                DEBUG_PRINT("Y: " << i.gen_y); \
                DEBUG_PRINT("FIT: " << i.fitness); \
                DEBUG_PRINT("PROB: " << i.prob << std::endl); \
                counter++; \
            } \
            DEBUG_PRINT("==========================GERAÇÃO GERADA==========================") \
        } while(0)
#else
    #define DEBUG_GEN(x)
    #define DEBUG_PRINT(x)
#endif
