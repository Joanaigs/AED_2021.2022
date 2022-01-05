#ifndef AED_PROJ1_2021_AVIAO_H
#define AED_PROJ1_2021_AVIAO_H

#include <string>
#include <list>
#include <queue>
#include <stack>
#include "voos.h"
#include "servico.h"
#include "uteis.h"


class Aviao{
public:
    /**
     * Construtor (sem parâmetros) da classe avião.
     */
    Aviao();

    /**
     * Construtor da classe avião
     * @param matricula é a matricula do avião
     * @param capacidade é a capacidade (número de lugares existentes) do avião
     */
    Aviao(std::string matricula, unsigned capacidade);

    /**
     * Para cada avião existem ficheiros com os dados relativos aos servicos por realizar nele, por ordem crescente de data.
     * Esta função lê estes dados e coloca-os na fila "servicosPorRealizar".
     */
    void setServicosPorRealizar();

    /**
     * Para cada avião existem ficheiros com os dados relativos aos servicos realizados nele, por ordem crescente de data.
     */
    void setServicosRealizados();
    std::string getMatricula() const;
    unsigned getCapacidade() const;
    std::list<Voos> getPlanoVoo() const;
    void setPlanoVoo();
    std::queue<Servico> getServicosPorRealizar() const;
    std::queue<Servico> getServicosRealizados() const;
    bool realizarServico();
    void updateServicosFile(const std::string& filename, std::queue<Servico> servicos);
    void mostrarServicos();
    void mostrarPlanoVoo();
    bool adicionarServico();
    void apagarVoo(unsigned int numeroVoo);
    bool adicionarVoo(bool &terminar);
    void updatePlanoVooFile(std::string filename);
    void updatePlanoVoo(list<Voos> planoVoo);

private:
    std::string matricula;
    unsigned capacidade;
    std::list<Voos> planoVoo;
    std::queue<Servico> servicosPorRealizar;
    std::queue<Servico> servicosRealizados;
    std::vector<Passageiro> passageirosVoo;   // permite saber quantos passageiros o voo já tem com passageirosVoo.size()

};

#endif //AED_PROJ1_2021_AVIAO_H
