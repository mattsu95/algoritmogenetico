#include "AlgoritmoGenetico.h"

using namespace std;

float GetFitness(float x, float y) {
    // 2x² - 13x + xy - 7y/3
    return (2*(x*x) - 13*x + x*y - (7*y)/3);
} 

Individuo::Individuo(std::string x, std::string y, float z): gen_x(x), gen_y(y), fitness(z){}

Populacao::Populacao(int gen, unsigned int pop_size, double tax_mut, double tax_rep) : gen(gen), pop_size(pop_size), tax_mut(tax_mut), tax_rep(tax_rep) {}

Populacao::~Populacao(){}

void Populacao::AdicionarIndividuo(string x, string y) {
    float fX = Generations::BinaryToFloat(x);
    float fY = Generations::BinaryToFloat(y);

    float z = GetFitness(fX, fY);
    subjects.emplace_back(x, y, z);
    pop_size = subjects.size();
    fitness_global.emplace_back(z);
}

double Populacao::UpdateFitness(){
    return fitness_medio = accumulate(fitness_global.begin(), fitness_global.end(), 0.0) / static_cast<double>(fitness_global.size());
}

vector<string> Populacao::Cruzamento(Individuo a, Individuo b) { //função de cruzamento (uniforme)
    //a máscara define se o filho vai pegar um bit do individuo a(0) ou do individuo b(1)
    string mascara = "00110.110"; 
    string xa = a.gen_x;
    string xb = b.gen_x;
    string ya = a.gen_y;
    string yb = b.gen_y;
    string x = mascara, y = mascara;
    int len = xa.length();

    for(int i = 0; i < len; i++) {
        DEBUG_PRINT("[CRUZANDO PROCESS] : mascara: " << mascara << " | mascara[i]: " << mascara[i] << " | x: "<< x << " | y: " << y << " | xa: " << xa << " | xb: " << xb << " | len: " << len << " | ya: " << ya << " | yb: " << yb);
        if(mascara[i] == '0') {
            x[i] = xa[i];
            y[i] = ya[i];
        }
        else if(mascara[i] == '1') {
            x[i] = xb[i];
            y[i] = yb[i];
        }
        else {
            x[i] = '.';
            y[i] = '.';
        }
    }

    DEBUG_PRINT("[CRUZAMENTO] " << "X: " << x << "| y: " << y);
    AdicionarIndividuo(x, y);
    Mutacao(&subjects.back());

    return vector<string>() = {x, y}; //depois de retornar ainda tem que adicionar na população
} 

void Populacao::Mutacao(Individuo *a) { //função de mutação (inversão dos bits)
    if(Generations::RandomFloat(0.0f, 1.001f) > tax_mut){ return; } // Chance de mutação

    string x = a->gen_x;
    string y = a->gen_y;

    int len = x.length();

    for(int i = 0; i < len; i++) {
        if(x[i] != '.') x[i] = x[i] == '0'? '1': '0';
        if(y[i] != '.') y[i] = y[i] == '0'? '1': '0';
    }

    a->gen_x = x;
    a->gen_y = y;
} 

void Populacao::Sort() {
    subjects.sort([](const Individuo& a, const Individuo& b) {
        return a.fitness < b.fitness;
    });
}

Individuo Populacao::Select() {
    float random = Generations::RandomFloat(0.0f, 1.00001f);

    DEBUG_PRINT ("[SELECT] random = " << random);

    double acumulated = 0;

    for(auto i = subjects.begin(); i != subjects.end(); ++i) {
        acumulated += i->prob;
        if(acumulated >= random) return *i; //retorna como cópia
    }

    return subjects.back();
}

void Populacao::Ranking() {
    Sort();
    int sumrank = (pop_size * (pop_size+1)) / 2;

    int rank = 1;
    for(auto i = subjects.begin(); i != subjects.end(); ++i, ++rank) {
        i->prob = static_cast<float>(rank) / static_cast<float>(sumrank);
    }
}