//
// Created by jigs2 on 12/12/2021.
//

#ifndef AED_PROJ1_2021_ORDENAR_H
#define AED_PROJ1_2021_ORDENAR_H

class Voo;

#include "passageiro.h"
#include "voos.h"


bool passageiroPeloNomeCrescente( Passageiro p1, Passageiro p2) {
    return (p1.getNome() < p2.getNome());
}

bool passageiroPeloNomeDecrescente(Passageiro p1, Passageiro p2) {
    return (p2.getNome() < p1.getNome());
}

bool passageiroPelaIdadeCrescente(Passageiro p1,  Passageiro p2) {
    return (p1.getDataNascimento() < p2.getDataNascimento());
}

bool passageiroPelaIdadeDecrescente(Passageiro p1,  Passageiro p2) {
    return (p2.getDataNascimento() < p1.getDataNascimento());
}

bool planoVooPorDuracaoCrescente(Voos &v1,  Voos &v2) {
    return (v1.getDuracaoVoo() < v2.getDuracaoVoo());
}

bool planoVooPorDuracaoDecrescente(Voos &v1, Voos &v2) {
    return (v2.getDuracaoVoo() < v1.getDuracaoVoo());
}

bool planoVooPorDataPartidaCrescente(Voos &v1,  Voos &v2) {
    return (v1.getDataPartida() < v2.getDataPartida());
}

bool planoVooPorDataPartidaDecrescente(Voos &v1,  Voos &v2) {
    return (v2.getDataPartida() < v1.getDataPartida());
}

bool planoVooPorPreçoCrescente(Voos &v1,  Voos &v2) {
    return (v1.getPreco() < v2.getPreco());
}

bool planoVooPorPreçoDecrescente(Voos &v1, Voos &v2) {
    return (v2.getPreco() < v1.getPreco());
}

#endif //AED_PROJ1_2021_ORDENAR_H
