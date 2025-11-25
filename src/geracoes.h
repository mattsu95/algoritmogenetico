#pragma once

#include <random>

class Populacao;

namespace Generations{
    float RandomFloat(int a, int b);
    
    int RandomInteger(int a, int b);

    Populacao* create_new(unsigned int pop_size);

    Populacao* create_next();
}
