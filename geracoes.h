#ifndef GERACOES_H
#define GERACOES_H

#include <iostream>
#include <random>
#include "debug.h"
#include "ag.h"

namespace Generations{
    float RandomFloat();

    Populacao* create_new(unsigned int pop_size);

    Populacao* create_next();
}

#endif