#include "AlgoritmoGenetico.h"

using namespace std;

/*
    TEM Q FAZER UMA INTERFACE QUE É ONDE VAI SER DEFINIDO O TAMANHO DA POPULAÇÃO, O NÚMERO DE GERAÇÕES (CRITÉRIO DE PARADA), E AS TAXAS
    DE CRUZAMENTO E MUTAÇÃO

    eu não faço ideia de como q faz os gráfico e os crl; se n me engano o b-word falo 
    q ia disponibilziar um exemplo mas até agora nada
*/

float GetFitness(float x, float y) {
    // 2x² - 13x + xy - 7y/3
    return (2*(x*x) - 13*x + x*y - (7*y)/3);
} 

Individuo::Individuo(std::string x, std::string y, float z): gen_x(x), gen_y(y), fitness(z){}



Populacao::Populacao(){ //essa construção só vale pra primeira geração; provavelmente vai ter que mudar isso
    string x = FloatToBinary(-15.0f);
    string y = FloatToBinary(-15.0f);
    float z = GetFitness(-15.0f, -15.0f);

    subjects.emplace_back(x, y, z);
    
    fitness_global.emplace_back(z);
    fitness_medio = accumulate(fitness_global.begin(), fitness_global.end(), 0) / fitness_global.size();
}

Populacao::~Populacao(){}

void Populacao::AdicionarIndividuo(float x, float y) {
    float z = GetFitness(x, y);
    subjects.emplace_back(FloatToBinary(x), FloatToBinary(y), z);
    pop_size = subjects.size();
    fitness_global.emplace_back(z);
}

float Populacao::UpdateFitness(){
    return fitness_medio = accumulate(fitness_global.begin(), fitness_global.end(), 0) / fitness_global.size();
}

string Populacao::FloatToBinary(float f) { //armazenar em cada indivíduo       -> dá pra chamar a função de Code
    int integer = static_cast<int>(f);
    float floating = f - integer;

    string binteger = integer < 0? "1": "0";
    if(integer == 0) binteger += "0";
    else {
        if(integer < 0) integer = -integer; //acho q n faz diferença fazer a operação com ele positivo ne?
        while(integer > 0) {
            binteger += integer%2? '1': '0';
            integer /= 2;
        }
        reverse(binteger.begin()+1, binteger.end()); //o +1 é pra manter o bit de sinal
    }


    string bfloating = "";
    int precisao = 3;
    if(floating == 0) bfloating = "0";
    else {
        if(floating < 0) floating = -floating;
        while(precisao > 0 && floating > 0) {
            floating *= 2;

            if(floating >= 1) {
                bfloating += '1';
                floating -= 1;
            }
            else bfloating += '0';

            precisao--;
        }
    }
    
    DEBUG_PRINT("Bin: " << "(" << f << ")" << binteger << "." << bfloating);

    return binteger + "." + bfloating; //isso aqui é coisa de python
}

float Populacao::BinaryToFloat(const string &s) { //usar para a função de otimização  -> dá pra chamar a função de Decode
    int inumber = 0;
    float f = 0;
    bool signal = s[0] == '1'? true: false;
    size_t intlen = s.find(".");
    size_t int_start = 1;
    size_t int_end = intlen - 1;

    int i = 0;
    int exp = 0;
    for(i = static_cast<int>(int_end); i >= static_cast<int>(int_start); i--, exp++) {
        if(s[i] == '1') inumber += (1 << exp); //multiplicando por potencia de 2
    }
    
    exp = -1;
    for(i = static_cast<int>(intlen) + 1; i < static_cast<int>(s.size()); i++, exp--) {
        if(s[i] == '1') f += pow(2.0, exp);
    }
    
    float result = static_cast<float>(inumber) + f;
    if(signal) result = -result;
    
    return result;
} 

Individuo Populacao::Cruzamento(Individuo a, Individuo b) { //função de cruzamento (uniforme)
    //a máscara define se o filho vai pegar um bit do individuo a(0) ou do individuo b(1)
    string mascara = "00110.110"; 
    string xa = a.gen_x;
    string xb = b.gen_x;
    string ya = a.gen_y;
    string yb = b.gen_y;
    string x, y;
    int len = xa.length();

    for(int i = 0; i < len; i++) {
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

    float xf = BinaryToFloat(x);
    float yf = BinaryToFloat(y);
    float z = GetFitness(xf, yf);

    Individuo c(x, y, z);

    return c; //depois de retornar ainda tem que adicionar na população
} 

void Populacao::Mutacao(Individuo *a) { //função de mutação (inversão dos bits)
    //a gnt tem que definir a taxa de mutação, mas isso dá pra mexer quando as gerações estiverem ocorrendo
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

void Populacao::Ranking() {
    int sumrank = (pop_size * (pop_size+1)) / 2;
    
    int rank = 1;
    for(auto i = subjects.begin(); i != subjects.end(); ++i, ++rank) {
        i->prob = static_cast<float>(rank) / static_cast<float>(sumrank);
    }
}


/*elitismo acho que não precisa função, só pegar o indivíduo retornado da função de seleção
e passar pra proxima geração (posso estar errado)*/