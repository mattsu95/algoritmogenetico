#ifndef GERACOES_H
#define GERACOES_H

#include "pbplots/pbPlots.hpp"
#include "pbplots/supportLib.hpp"

#include <random>
#include <list>
#include <fstream>

class Populacao;

namespace Generations{
    inline unsigned int POP_SIZE;
    inline int GEN;
    inline double TAX_MUT;
    inline double TAX_REP;
    
    float RandomFloat(float a, float b);
    
    int RandomInteger(int a, int b);

    void SalvarLog(const std::vector<Populacao> populacoes);

    std::string FloatToBinary(float f);
    
    float BinaryToFloat(const std::string &s);

    void PlotGraph(std::vector<Populacao> geracoes);

    std::string RandomBin();

    Populacao* create_new(unsigned int pop_size, double tax_mut, double tax_rep);

    Populacao* create_next(Populacao gen_anterior);
}

#endif