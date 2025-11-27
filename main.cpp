#include <AlgoritmoGenetico.h>
#include <menu.h>

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

    int taxa_cruzamento = 78, taxa_mutacao = 4;
    int tamanho_populacao = 10;
    int num_geracoes = 5;
    std::vector<int*> propriedades = {&tamanho_populacao, &num_geracoes, &taxa_cruzamento, &taxa_mutacao};

    while(1){
        // Reseta valor de gerações
        num_geracoes = 5;

        // Inicia o menu interativo
        int starting = start_menu(propriedades);
        if(!starting){ break; }

        // Valore dde LOG
        std::list<Populacao> geracoes_list;
        std::list<double> fitness_medio;

        // Primeira geração com números aleatórios
        Populacao* gen_atual = Generations::create_new(tamanho_populacao, taxa_mutacao/100.0f, taxa_cruzamento/100.0f); // Cria uma nova geração

        while (num_geracoes > 0)
        {
            DEBUG_GEN(gen_atual);

            // Salvar os dados da população atual
            // Atualiza os dados pro LOG
            fitness_medio.emplace_back(gen_atual->UpdateFitness());
            geracoes_list.emplace_back(*gen_atual);

            // Selecionar indicíduos com o fitness
            Populacao* prox_gen = Generations::create_next(*gen_atual);

            // Atualiza a geração atual com a próxima
            delete gen_atual; // Evita vazamento de memória
            gen_atual = prox_gen;

            num_geracoes--;
        }

        // Salva informações no arquivo de log
        Generations::SalvarLog(geracoes_list);

        // Limpa pro próximo loop
        delete gen_atual;

        std::cout << "========= O Algoritmo Rodou com sucesso =========" << std::endl;
        std::cout << "========= Pressione Enter para voltar ao menu =========" << std::endl;
        getch();
    }

    return 0;
}