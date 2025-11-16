#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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
public:
    string gen_x, gen_y;
    string fitness; //z
    Individuo* next;

    Individuo(string x, string y, string z): gen_x(x), gen_y(y), fitness(z), next(nullptr){}
};

class Populacao { //não sei direito como q vamos interagir com as gerações e os crl
public:
    Individuo* head;
    Individuo* tail; //facilitar pra adicionar novos individuos

    Populacao(){
        string x = FloatToBinary(-15);
        string y = FloatToBinary(-15);
        float z = Otimizacao(-15, -15);
        string fitness = FloatToBinary(z);

        Individuo h(x, y, fitness);
        head = tail = &h;
    }

    void AdicionarIndividuo() {}


    string FloatToBinary(float f) { //armazenar em cada indivíduo       -> dá pra chamar a função de Code
        int integer = static_cast<int>(f);
        float floating = f < 0? f + integer: f - integer;

        //viuuuuuuuu faz aqui aquele bagulho pra preencher uma string com 0, q eu n sei como faz
        //vamo usar 6 bits pra inteiro e 3 pra float, daí
        //cara, na real q os 5 bits seriam só pros genes x e y, pro fitness precisaria de pelo menos 10
        //então acho q faz um if pra se o |integer| for <= 15, usa 6 bits só; e se for maior, usa mais (acho q uns 12 ou 13 já da conta)

        string binteger = integer < 0? "1": "0";
        if(integer == 0) binteger += "0";            
        else {
            if(integer < 0) integer = -integer; //acho q n faz diferença fazer a operação com ele positivo ne?
            while(integer > 0) {
                binteger += integer%2? '1': '0';
                integer /= 2;
            }
            reverse(binteger.begin(), binteger.end()); //q função gostosa slk
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
        
        return binteger + "." + bfloating; //isso aqui é coisa de python
    } 

    float BinaryToFloat(string s) {} //usar para a função de otimização  -> dá pra chamar a função de Decode

    Individuo Sexo(Individuo a, Individuo b) { //função de cruzamento (uniforme) -> não sei se recebe/retorna ponteiro ou se assim ta certo
        //a máscara define se o filho vai pegar um bit do individuo a(0) ou do individuo b(1)
        string mascara = "01010.010"; //coloquei esse só como placeholder, vamo mudar dps
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
        float z = Otimizacao(xf, yf);
        string fitness = FloatToBinary(z);

        Individuo c(x, y, fitness);

        return c; //depois de retornar ainda tem que adicionar na população
    } 

    void Mutacao(Individuo *a) { //função de mutação (inversão dos bits)
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

        //como passei um ponteiro pro individuo, já tá alterando direto nele, né? não precisa retornar ele, certo?
    } 
};

class Geracoes {}; //chapei demais? -> se for usar isso aqui, vai ter q mudar a construção da classe da população, pq aquela só vai valer pra primeir geração


Individuo Select(Populacao p) {} //função de seleção (por ranking)





/*elitismo acho que não precisa função, só pegar o indivíduo retornado da função de seleção
e passar pra proxima geração (posso estar errado)*/

float Otimizacao(float x, float y) {

    return (2*(x*x) - 13*x + x*y - (7*y)/3); //não precisa operar 100% com binário, né? 🥺
} 