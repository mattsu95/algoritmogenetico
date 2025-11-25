// run code
// g++ main.cpp ag.cpp ag.h geracoes.cpp geracoes.h
#include <AlgoritmoGenetico.h>

//using namespace std;

int main(){
    // Menu e interações
        // taxa de cruzamento e mutação
        // Tamanho da população
        // num_generations

    // Cria a primeira geração=====================================DONE
    // Gerações lista==============================================DONE
    // Fitness médio lista=========================================DONE

    // While (Critério de parada)
        // Roda o fitness(ger atual)===============================DONE
        // Seleção com o fitness===================================
        // Salva o elitista

        // fitness médio lista <- fitness médio resultado
        // Roda o log da geração atual(valores da geração, fitness médio, melhor fitness, melhor x e y)
        // Gráfico e os krl com os resultaddos

        // Verificar critério de parada

        // Cruzamento (Orgia binária)
            // Mutação
        // Cria e ger atual <- próxima geração
    // end While

    float taxa_cruzamento, taxa_mutacao;
    int tamanho_populacao = 1;
    int num_geracoes = 5;

    std::list<Populacao> geracoes_list;
    std::list<float> fitness_medio;

    Populacao* gen_atual = Generations::create_new(tamanho_populacao); // Cria uma nova geração
    //cout << gen_atual->subjects.front().gen_x << endl;

    int counter = 0;
    DEBUG_PRINT("==========================GERAÇÃO GERADA==========================")
    for(auto i : gen_atual->subjects){
        DEBUG_PRINT("INDIVIDUO " << counter);
        DEBUG_PRINT("X: " << i.gen_x);
        DEBUG_PRINT("Y: " << i.gen_y); 
        DEBUG_PRINT("FIT: " << i.fitness);
        DEBUG_PRINT("PROB: " << i.prob << std::endl);
        counter++;
    }
    DEBUG_PRINT("==========================GERAÇÃO GERADA==========================")

    while (num_geracoes > 0)
    {
        // Selecionar indicíduos com o fitness
        

        num_geracoes--;
    }
    

    return 0;
}