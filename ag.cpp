#include <iostream>
#include <string>
#include <vector>

using namespace std;

//coisas do pdf q não entendi com 1000% de clareza: 
/*
    "Os paraˆmetros empregados ao longo da execuc ̧ a ̃o devem ser definidos na interface do 
    sistema: taxas de cruzamento e mutac ̧ a ̃o, tamanho da populac ̧ a ̃o e nu ́ mero de gerac ̧o ̃es";

    //tá, acho que entendi. A gente precisa definir a taxa de cruzamento e mutação, o tamanho da população e o número de gerações, né?

    nmrl q a gnt vai ter q operar com float?
    eu não faço ideia de como q faz os gráfico e os crl; se n me engano o b-word falo 
    q ia disponibilziar um exemplo mas até agora nada
*/

struct Individuo { 
    unsigned gen_x, gen_y;
    unsigned fitness; //z
    Individuo* next;

    Individuo(float x, float y): gen_x(x), gen_y(y), fitness(905), next(nullptr) {}
};

class Populacao { //não sei direito como q vamos interagir com as gerações e os crl
public:
    Individuo* base;
    Populacao(){
        Individuo b(-15, -15);
        base = &b;
    }

    unsigned FloaToBinary(float f) {}   //armazenar em cada indivíduo       -> dá pra chamar a função de Code
    unsigned BinaryToFloat(unsigned) {} //usar para a função de otimização  -> dá pra chamar a função de Decode
};

class Geracoes {}; //chapei demais?


Individuo Select(Populacao p) {} //função de seleção (por ranking)

Individuo Sexo(Individuo x, Individuo y) {} //função de cruzamento (uniforme)

Individuo Mutacao(Individuo x) {} //função de mutação (inversão dos bits)

/*elitismo acho que não precisa função, só pegar o indivíduo retornado da função de seleção
e passar pra proxima geração (posso estar errado)*/

float Otimizacao(float x, float y) {
    //tb n entendi qual é a dos valores base

    return (2*(x*x) - 13*x + x*y - (7*y)/3);
} 