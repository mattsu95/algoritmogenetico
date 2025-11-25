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
float Otimizacao(float x, float y);

// Classe População
class Populacao { 
public:
    std::list<Individuo> subjects;
    std::list<float> fitness_global;
    float fitness_medio = 904;
    int pop_size = 1;

    // Construtor
    Populacao();
    
    // Destrutor (Recomendado para limpar a lista encadeada)
    ~Populacao(); 

    // Métodos
    void AdicionarIndividuo(float x, float y); // A ser implementado
    float UpdateFitness();

    // Métodos de Conversão
    std::string FloatToBinary(float f);
    float BinaryToFloat(const std::string &s);

    // Operadores Genéticos
    Individuo Cruzamento(Individuo a, Individuo b);
    void Mutacao(Individuo *a);
    void Sort();
    void Ranking();
};

// Classe Gerações (Placeholder conforme seu código original)
class Geracoes {
    // Adicionar métodos estáticos ou membros conforme necessário
    // ex: static void create_new();
};
