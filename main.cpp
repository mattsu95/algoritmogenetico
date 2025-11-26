// run code
// g++ main.cpp ag.cpp ag.h geracoes.cpp geracoes.h
#include <AlgoritmoGenetico.h>
#include <util.h>

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
        // Salva o elitista========================================DONE
        
        // fitness médio lista <- fitness médio resultado==========DONE
        // Roda o log da geração atual=============================DONE
        // Gráfico e os krl com os resultaddos TODO

        // Seleção com o fitness===================================DONE
            // Cruzamento
                // Mutação
            // Cria e ger atual <- próxima geração

        // Verificar critério de parada============================DONE

    // end While

    float taxa_cruzamento = 0.78, taxa_mutacao = 0.045;
    int tamanho_populacao = 10;
    int num_geracoes = 5;

    // Valore dde LOG
    std::list<Populacao> geracoes_list;
    std::list<double> fitness_medio;

    Populacao* gen_atual = Generations::create_new(tamanho_populacao, taxa_mutacao, taxa_cruzamento); // Cria uma nova geração
    //cout << gen_atual->subjects.front().gen_x << endl;

    Individuo i = gen_atual->Select();
    DEBUG_PRINT("INDIVIDUO SELECIONADO");
    DEBUG_PRINT("X: " << i.gen_x);
    DEBUG_PRINT("Y: " << i.gen_y); 
    DEBUG_PRINT("FIT: " << i.fitness);
    DEBUG_PRINT("PROB: " << i.prob << std::endl);

    while (num_geracoes > 0)
    {

        DEBUG_GEN(gen_atual);
        
        // Salvar os dados da população atual
        // Atualiza os dados pro LOG
        fitness_medio.emplace_back(gen_atual->UpdateFitness());
        geracoes_list.emplace_back(*gen_atual);
        // Salva LOG
        //Generations::SalvarLog(geracoes_list.back());

        // Populacao last_gen = geracoes_list.back();
        DEBUG_PRINT("================ GERAÇÃO [" << last_gen.gen << "] ================");
        DEBUG_PRINT("GERAÇÃO NÚMERO:    \t" << last_gen.gen);
        DEBUG_PRINT("TAMANHO POPULAÇÃO: \t" << last_gen.pop_size);
        DEBUG_PRINT("TAXA DE MUTAÇÃO:   \t" << last_gen.tax_mut);
        DEBUG_PRINT("TAXA REPRODUÇÃO:   \t" << last_gen.tax_rep);
        DEBUG_PRINT("FITNESS MÉDIO:     \t" << last_gen.fitness_medio);
        Individuo gym_rat = last_gen.subjects.back();
        DEBUG_PRINT("MELHOR FITNESS:    \t" << gym_rat.fitness);
        DEBUG_PRINT("MELHOR X:          \t" << gym_rat.gen_x);
        DEBUG_PRINT("MELHOR Y:          \t" << gym_rat.gen_y);
        DEBUG_PRINT("================ GERAÇÃO [" << last_gen.gen << "] ================");
        DEBUG_PRINT("");
        // =================================================================================
        
        // Selecionar indicíduos com o fitness (atualiza a população atual)
        gen_atual = Generations::create_next(*gen_atual);

        num_geracoes--;
    }

    Generations::SalvarLog(geracoes_list);

    return 0;
}