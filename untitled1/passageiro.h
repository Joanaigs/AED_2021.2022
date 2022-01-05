#ifndef AED_PROJ1_2021_PASSAGEIRO_H
#define AED_PROJ1_2021_PASSAGEIRO_H

#include <vector>
#include <string>
#include "bilhete.h"

class Bagagem;
class Bilhete;
class Passageiro{
public:
    Passageiro();
    Passageiro(std::string nome, std::string dataNascimento);
    Passageiro(std::string nome, std::string dataNascimento, bool bagagemAutomatica);
    Passageiro(std::string nome, std::string dataNascimento, bool bagagemAutomatica, Bilhete bilhete);
    void setNome(std::string nome);
    void setDataNascimento(std::string dataNascimento);
    void setBagagemAutomatica(bool bagagemAutomatica);
    void setBagagem(Bagagem bagagem);
    void setBilhete(Bilhete bilhete);
    std::string getNome();
    std::string getDataNascimento();
    bool getBagagemAutomatica();
    Bagagem getBagagem();
    Bilhete getBilhete();
    bool operator==(Passageiro& p2);
    void mostrarPassageiro();

private:
    std::string nome, dataNascimento;
    bool bagagemAutomatica;
    Bilhete *bilhete;
};

#endif //AED_PROJ1_2021_PASSAGEIRO_H
