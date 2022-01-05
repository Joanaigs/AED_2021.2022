#ifndef AED_PROJ1_2021_BAGAGEM_H
#define AED_PROJ1_2021_BAGAGEM_H
#include "passageiro.h"

class Bagagem{
    static constexpr double stamanhoMaxBagagem = 158.0;  //em centimetros
    static constexpr double pesoMaxBagagem = 32.0;      //em quilogramas
public:
    Bagagem();
    Bagagem(std::string nomePassageiro, double peso, double tamanho);
    std::string getNomePassageiro();
    double getPeso();
    double getTamanho();


private:
    std::string nomePassageiro;
    double peso, tamanho;
};


#endif //AED_PROJ1_2021_BAGAGEM_H
