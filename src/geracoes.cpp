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

    std::string FloatToBinary(float f){
        int integer = static_cast<int>(f);
        float floating = f - integer;

        std::string binteger = integer < 0? "1": "0";
        if(integer == 0) binteger += "0";
        else {
            if(integer < 0) integer = -integer;
            while(integer > 0) {
                binteger += integer%2? '1': '0';
                integer /= 2;
            }
            size_t len = binteger.size();
            if(len < 5) 
                for(int i = 0; i < 5 - static_cast<int>(len); i++) binteger += '0';
            reverse(binteger.begin()+1, binteger.end()); //o +1 é pra manter o bit de sinal
        }


        std::string bfloating = "";
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

        if(precisao)
            for(int i = 0; i < precisao; i++) bfloating += '0';
        
        DEBUG_PRINT("Bin: " << "(" << f << ")" << binteger << "." << bfloating);

        return binteger + "." + bfloating;
    }

    float BinaryToFloat(const std::string &s){
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