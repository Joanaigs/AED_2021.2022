#include "Servico.h"
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;


Servico::Servico(string data, string tipoServico, string funcionario) {
    this->data=data;
    this->tipoServico=tipoServico;
    this->funcionario=funcionario;
}

void Servico::mostrarServico() {
    cout << setw(19) << funcionario << setw(25) << tipoServico << setw(20) << data<<endl;
}

string Servico::getData(){
    return data;
}

string Servico::getTipoServico(){
    return tipoServico;
}

string Servico::getFuncionario(){
    return funcionario;
}
