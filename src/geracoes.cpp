#include "AlgoritmoGenetico.h"
#include "geracoes.h"

namespace Generations{

    float RandomFloat(float a, float b){
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(a, b);
        return dis(gen);
    }
    
    int RandomInteger(int a, int b){
        if(b >= a) {  }
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(a, b);
        return dis(gen);
    }

    void SalvarLog(const std::list<Populacao> populacoes){
        std::ofstream arquivo("log.txt", std::ios::ate);
        
        if(arquivo.is_open()){
            for(auto pop : populacoes){
                Individuo best_individuo = pop.subjects.back();
                
                arquivo << "================ GERAÇÃO [" << pop.gen << "] ================\n";
                arquivo << "GERAÇÃO NÚMERO:    \t" << pop.gen << "\n";
                arquivo << "TAMANHO POPULAÇÃO: \t" << pop.pop_size << "\n";
                arquivo << "TAXA DE MUTAÇÃO:   \t" << pop.tax_mut << "\n";
                arquivo << "TAXA REPRODUÇÃO:   \t" << pop.tax_rep << "\n";
                arquivo << "FITNESS MÉDIO:     \t" << pop.fitness_medio << "\n";
                arquivo << "MELHOR FITNESS:    \t" << best_individuo.fitness << "\n";
                arquivo << "MELHOR X:          \t" << best_individuo.gen_x << "\n";
                arquivo << "MELHOR Y:          \t" << best_individuo.gen_y << "\n";
                arquivo << "==================================================\n\n";
            }
            
            arquivo.close();
        } else{
            std::cerr << "Erro ao abrir arquivo de log!" << std::endl;
        }
    }

    std::string RandomBin(){
        std::string bin = "";

        DEBUG_PRINT("+======BIN_TEST======+");
        for(int i = 0; i < 9; i++){
            if(i == 5) {
                bin += '.';
                if(bin == "11111." || "01111.") {
                    bin += "000";
                    return bin;
                }
                continue;
            }

            int b = RandomInteger(0, 1000);
            bin += (b % 2)? '1': '0';
        }

        return bin;
    }

    Populacao* create_new(unsigned int pop_size, double tax_mut, double tax_rep){
        DEBUG_PRINT("----- CREATE NEW GENERATION -----");
        POP_SIZE = pop_size;
        TAX_MUT = tax_mut;
        TAX_REP = tax_rep;

        Populacao* new_pop = new Populacao(GEN, POP_SIZE, TAX_MUT, TAX_REP);
        
        for(unsigned int i = 0; i < pop_size; i++){
            // Gerar valores aleatórios
            // dois números entre 15 e -15
            // fitness tem q calcular com otimização
            //float x = RandomFloat(-15, 15.0001);
            //float y = RandomFloat(-15, 15.0001);

            // Gerar binário direto
            // 11111.000
            std::string x = RandomBin();
            std::string y = RandomBin();

            DEBUG_PRINT("X GEN " << x << " ");
            DEBUG_PRINT("Y GEN " << y << " ");
            
            new_pop->AdicionarIndividuo(x, y);
            DEBUG_PRINT("INDIVIDUO ALEATÓRIO ADICIONADO");
            DEBUG_PRINT(" ");
        }
        new_pop->Ranking();

        DEBUG_PRINT("----- END CREATE NEW GENERATION -----");
        return new_pop;
    }

    Populacao *create_next(Populacao gen_anterior){
        // Criar nova população com o select
        GEN++;
        Populacao* new_pop = new Populacao(GEN, POP_SIZE, TAX_MUT, TAX_REP);
        
        // Selecionar POP_SIZE pares para acasalar
        for(int i = 0; i < POP_SIZE; i++){
            Individuo a = gen_anterior.Select();
            Individuo b = gen_anterior.Select();
            DEBUG_PRINT("INDV A: " << a.gen_x << " | " << a.gen_y << " | " << a.fitness);
            DEBUG_PRINT("INDV B: " << b.gen_x << " | " << b.gen_y << " | " << b.fitness);
            
            // cruzar
            if(RandomFloat(0.0f, 1.001f) <= TAX_REP){
                // cruzar e mutar(dentro do cruzamento)
                new_pop->Cruzamento(a, b);
            }else{
                // se não cruzar, adiciona o melhor individuo entre os pais
                new_pop->AdicionarIndividuo(a.fitness > b.fitness ? a.gen_x, a.gen_y : b.gen_x, b.gen_y);
            }

        }

        new_pop->Ranking();

        return new_pop;
    }
}