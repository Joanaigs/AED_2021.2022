#include "bagagem.h"

Bagagem::Bagagem() {}

Bagagem::Bagagem(std::string nomePassageiro,double peso, double tamanho): nomePassageiro(nomePassageiro), peso(peso), tamanho(tamanho) {}

std::string Bagagem::getNomePassageiro() {
    return nomePassageiro;
}

double Bagagem::getPeso() {
    return peso;
}

double Bagagem::getTamanho() {
    return tamanho;
}


