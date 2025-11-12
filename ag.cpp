#include <iostream>
#include <string>
#include <vector>

using namespace std;

//coisas do pdf q não entendi com 1000% de clareza: 
/*
    "Os paraˆmetros empregados ao longo da execuc ̧ a ̃o devem ser definidos na interface do 
    sistema: taxas de cruzamento e mutac ̧ a ̃o, tamanho da populac ̧ a ̃o e nu ́ mero de gerac ̧o ̃es";

    nmrl q a gnt vai ter q operar com float?
    eu não faço ideia de como q faz os gráfico e os crl; se n me engano o b-word falo 
    q ia disponibilziar um exemplo mas até agora nada
*/

class Individuo {};
class Populacao {};

Individuo Select(Populacao p) {} //função de seleção (por ranking)

Individuo Sexo(Individuo x, Individuo y) {} //função de cruzamento (uniforme)

Individuo Mutacao(Individuo x) {} //função de mutação (inversão dos bits)

/*elitismo acho que não precisa função, só pegar o indivíduo retornado da função de seleção
e passar pra proxima geração (posso estar errado)*/

float Otimizacao(int x, int y) { //função de otimização -> ela recebe int mesmo? ela retorna o fitness né?
    //não entendi as restrições da função (x ∈[−15,15], y ∈[−15,15])
    //tb n entendi qual é a dos valores base

    return (2*(x*x) - 13*x + x*y - (7*y)/3); //provavelmente não é simples assim. e não sei se é 7y/3 ou 7^(y/3)
} 

//acho que precisa de uma função pra codificação também, mas não tenho ctz de como deveria ser feita