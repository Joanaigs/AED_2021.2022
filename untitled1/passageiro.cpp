#include "passageiro.h"
#include <iostream>
#include <iomanip>

using namespace std;


Passageiro::Passageiro(string nome, string dataNascimento) {
    this->nome = nome;
    this->dataNascimento = dataNascimento;
}

Passageiro::Passageiro(string nome, string dataNascimento, bool bagagemAutomatica, Bilhete bilhete): nome(nome), dataNascimento(dataNascimento), bagagemAutomatica(bagagemAutomatica), bilhete(&bilhete){};

string Passageiro::getNome(){
    return nome;
}

void Passageiro::setNome(std::string nome){
    this->nome = nome;
}

void Passageiro::setDataNascimento(std::string dataNascimento){
    this->dataNascimento = dataNascimento;
}

void Passageiro::setBagagemAutomatica(bool bagagemAutomatica){
    this->bagagemAutomatica = bagagemAutomatica;
}


void Passageiro::setBilhete(Bilhete bilhete){
    this->bilhete = &bilhete;
}

string Passageiro::getDataNascimento(){
    return dataNascimento;
}

bool Passageiro::getBagagemAutomatica(){
    return bagagemAutomatica;
}



Bilhete Passageiro::getBilhete(){
    return *bilhete;
}

Passageiro::Passageiro(std::string nome, std::string dataNascimento, bool bagagemAutomatica) :nome(nome), dataNascimento(dataNascimento), bagagemAutomatica(bagagemAutomatica){};

void Passageiro::mostrarPassageiro() {
    cout<<setw(10)<< nome << setw(17) << dataNascimento << setw(20)
              << bagagemAutomatica<<endl;
}

bool Passageiro::operator==(Passageiro &p2) {
    return (nome==p2.getNome() && dataNascimento==p2.getDataNascimento());
}
