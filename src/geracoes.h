#ifndef GERACOES_H
#define GERACOES_H

#include <random>
#include <list>
#include <fstream>

inline unsigned int POP_SIZE;
inline int GEN;
inline double TAX_MUT;
inline double TAX_REP;

class Populacao;

namespace Generations{
    float RandomFloat(float a, float b);
    
    int RandomInteger(int a, int b);

    void SalvarLog(const std::list<Populacao> populacoes);

    std::string RandomBin();

    Populacao* create_new(unsigned int pop_size, double tax_mut, double tax_rep);

    Populacao* create_next(Populacao gen_anterior);
}

#endif