#pragma once

#include <string>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <list>

// Estrutura do Indivíduo
struct Individuo { 
    std::string gen_x;
    std::string gen_y;
    float prob;
    float fitness; // Valor z (resultado da otimização)
    

    // Construtor
    Individuo(std::string x, std::string y, float z);
};

// Declaração da Função de Otimização (Função Objetivo)
float GetFitness(float x, float y);

// Classe População
class Populacao { 
public:
    std::list<Individuo> subjects;
    std::list<float> fitness_global;
    double fitness_medio = 0;
    unsigned int pop_size = 0;
    double tax_mut;
    double tax_rep;
    int gen;

    // Construtor
    Populacao(int gen, unsigned int pop_size, double tax_mut, double tax_rep);
    
    // Destrutor
    ~Populacao(); 

    // Métodos
    void AdicionarIndividuo(std::string x, std::string y);
    double UpdateFitness();

    // Operadores Genéticos
    std::vector<std::string> Cruzamento(Individuo a, Individuo b);
    void Mutacao(Individuo *a);
    void Sort();
    Individuo Select();
    void Ranking();
};