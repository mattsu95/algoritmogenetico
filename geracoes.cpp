#include "geracoes.h"

namespace Generations{

    float RandomFloat(){
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(-15.0f, 15.0001f);
        return dis(gen);
    }

    Populacao* create_new(unsigned int pop_size){
        DEBUG_PRINT("----- CREATE NEW GENERATION -----");
        
        Populacao* new_pop = new Populacao();
        
        for(unsigned int i = 0; i < pop_size; i++){
            // Gerar valores aleatórios
            // dois números entre 15 e -15
            // fitness tem q calcular com otimização
            float x = RandomFloat();
            float y = RandomFloat();
            DEBUG_PRINT("X GEN " << x << " ");
            DEBUG_PRINT("Y GEN " << y << " ");
            
            new_pop->AdicionarIndividuo(x, y);
            DEBUG_PRINT("INDIVIDUO ALEATÓRIO ADICIONADO");
            DEBUG_PRINT(" ");
        }
        new_pop->Sort();
        new_pop->Ranking();

        DEBUG_PRINT("----- END CREATE NEW GENERATION -----");
        return new_pop;
    }

    Populacao *create_next(){



        return nullptr;
    }
}