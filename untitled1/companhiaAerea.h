//;
// Created by jigs2 on 08/12/2021.
//

#ifndef AED_PROJ1_2021_COMPANHIAAEREA_H
#define AED_PROJ1_2021_COMPANHIAAEREA_H
#include "aviao.h"
#include "uteis.h"
static Uteis util;

class CompanhiaAerea{
private:
    std::vector<Aviao> avioes;
public:
    CompanhiaAerea();
    void setAvioes();
    void addAviao(const Aviao aviao);
    void mostrarAvioes() const;
    std::vector<Aviao> getAvioes() const;
    void updateAvioesFile();
    Voos findVoo(int numeroVoo,  bool &found);
    Aviao findAviao(const string &matricula, bool &found);
    vector<Voos> findVoos(const string &info,  bool &found);
    bool servicoLimpeza(bool &terminar);
    bool adicionarServico(bool &terminar);
    bool adicionarVoo(bool &terminar);
    bool eliminarVoo(bool &terminar);
    bool comprarBilhete(bool &terminar);
    bool apagarBilhete(bool &terminar);
    bool checkIn(bool &terminar);
    bool adicionarAviao(bool &terminar);
    bool getAeroporto(Aeroporto aeroporto, bool &b);
};


#endif //AED_PROJ1_2021_COMPANHIAAEREA_H
