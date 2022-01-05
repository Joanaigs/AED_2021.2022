#ifndef AED_PROJ1_2021_VOOS_H
#define AED_PROJ1_2021_VOOS_H
#include <string>
#include <stack>
#include <list>
#include "passageiro.h"
#include "bagagem.h"
#include "aeroporto.h"

const int numCarruagensCarrinhoTransporte=3;
const int numPilhasPorCarruagem=4;
const int numMaxMalas=6;

class Aeroporto;
class Bagagem;
class Passageiro;
class Voos{
public:
    Voos();
    Voos(unsigned int numeroVoo, double duracaoVoo, std::string dataPartida, std::string origem, std::string destino, double preco, unsigned lugaresDisponiveis);
    unsigned int getNumeroVoo();
    double getDuracaoVoo();
    std::string getDataPartida();
    std::string getOrigem();
    std::string getDestino();
    Aeroporto *getAeroportoPartida() const;
    Aeroporto *getAeroportoChegada() const;
    double getPreco();
    void updatePassageiros(std::vector<Passageiro> passageirosVoo);
    unsigned getLugaresDisponiveis();
    void mostrarInfoVoo();
    bool operator==(Voos voo2) const;
    void setPassageiros();
    std::vector<Passageiro> getPassageiros();
    void updatePassageirosFile();
    void showPassageirosVoo();
    void adicionarPassageiro(Passageiro passageiros);
    void setBagagens();
    std::vector<std::vector<std::stack<Bagagem>>> getCarrinhoTransporte();
    void updateBagagemFile();
    bool adicionarBagagem(Bagagem bagagem);
private:
    unsigned int numeroVoo;
    double duracaoVoo, preco;
    std::string dataPartida;
    unsigned lugaresDisponiveis;
    Aeroporto *aeroportoPartida;
    Aeroporto *aeroportoChegada;
    std::vector<Passageiro> passageirosVoo;
    std::vector<std::vector<std::stack<Bagagem>>> carrinhoTransporte;
};


#endif //AED_PROJ1_2021_VOOS_H
