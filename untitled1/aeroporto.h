#ifndef AED_PROJ1_2021_AEROPORTO_H
#define AED_PROJ1_2021_AEROPORTO_H

#include "BST.h"
#include <vector>
#include <stack>
#include <queue>
#include "LocalTransporteTerrestre.h"

class LocalTransporteTerrestre;
class Aeroporto{
    BST<LocalTransporteTerrestre> transportes;
public:
    /**
     * Construtor (sem parâmetros) da classe Aeroporto.
     */
    Aeroporto():transportes(LocalTransporteTerrestre("", 0, vector<std::string>())){};

    /**
     * Construtor da classe Aeroporto.
     * @param nome é o nome do aeroporto
     */
    Aeroporto(std::string nome): nome(nome), transportes(LocalTransporteTerrestre("", 0, vector<std::string>())){};

    /**
     * Esta função constrói a BST responsável por guardar a informação sobre os locais de transporte terrestre, para cada aeroporto.
     */
    void setArvoreTransporte();

    /**
     * Esta função adiciona, nos dados relativos aos locais de transporte de um aeroporto selecionado, um novo local de transporte.
     * @param localTransporteTerrestre é o local de transporte terrestre que se pretende adicionar na base de dados.
     */
    void adicionaLocalTransporte(LocalTransporteTerrestre localTransporteTerrestre);

    /**
     * Esta função procura o local de transporte mais próximo do aeroporto selecionado pelo utilizador.
     * @return o local de transporte mais próximo do aeroporto, selecionado pelo utilizador.
     */
    LocalTransporteTerrestre encontraLocalMaisPerto();

    /**
     *
     * @return a BST (Bianry Search Tree) com a informação sobre os locais de transporte terrestre associados a um aeroporto.
     */
    BST<LocalTransporteTerrestre> getLocaisTransporte();

    /**
     * Esta função encontra um local de transporte, onde passe o transporte do tipo "tipoTransporte", passado como parâmetro,
     * à distância do aeroporto "distanciaDoAeroporto, também passada como parâmetro.
     * @param tipoTransporte é o tipo do transporte que se pretende encontrar.
     * @param distanciaDoAeroporto é a distância do aeroporto à qual se pretende apanhar o transporte.
     * @return o local de transporte onde passe o tipo de transporte selecionado, à distancia do aeroporto elegida.
     */
    LocalTransporteTerrestre encontraLocal(std::string &tipoTransporte, double distanciaDoAeroporto);

    /**
     * Esta função mostra a informação relativa aos transportes ao redor do aeroporto, que passem na paragem à hora passada como parâmetro.
     * Se não forem encontrados transportes a passarem a essa hora, então são mostrados os transportes que passem imediatamente antes, e imediatamente
     * depois da hora pretendida.
     * @param horaPartida é a hora a que o utilizador pretende apanhar o transporte.
     */
    void encontraLocais(string horaPartida) const;

    /**
     * Esta função mostra ao utilizador os horários e informações relativas aos locais de transporte em torno do aeroporto.
     */
    void printLocalTransporte();

    /**
     *
     * @return nome do aeroporto.
     */
    std::string getNome() const;
private:
    string nome;
};


#endif //AED_PROJ1_2021_AEROPORTO_H
