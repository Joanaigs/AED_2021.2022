#include "aeroporto.h"
#include <algorithm>
#include <fstream>
#include <sstream>


void Aeroporto::adicionaLocalTransporte(LocalTransporteTerrestre localTransporteTerrestre){
    transportes.insert(localTransporteTerrestre);
}

LocalTransporteTerrestre Aeroporto::encontraLocalMaisPerto() {
    return transportes.findMin();
}

BST<LocalTransporteTerrestre> Aeroporto::getLocaisTransporte() {
    return transportes;
}

LocalTransporteTerrestre Aeroporto::encontraLocal(string &tipoTransporte, double distanciaDoAeroporto) {
    return transportes.find(LocalTransporteTerrestre(tipoTransporte, distanciaDoAeroporto, vector<string>()));
}

void Aeroporto::encontraLocais(string horaPartida) const{
    queue<LocalTransporteTerrestre> resultado1;
    stack<LocalTransporteTerrestre> resultado2;
    BSTItrIn<LocalTransporteTerrestre> it(transportes);
    string min_max = "0";
    string max_min = "24:00";

    bool found = false;

    while (!it.isAtEnd()) {
        for(auto hora : it.retrieve().getHorario()){
            if(hora==horaPartida){
                resultado1.push(it.retrieve());
                found = true;
                break;
            }
            if(hora>horaPartida && hora<=max_min) {
                max_min = hora;
                resultado2.push(it.retrieve());
            }
            else if(hora<horaPartida && hora>=min_max) {
                min_max = hora;
                resultado2.push(it.retrieve());
            }
        }
        it.advance();
    }

    if(found) {
        cout << "Estas sao as informacoes sobre os transportes que partem as " << horaPartida << ":\n";
        while(resultado1.size()>0){
            cout << endl << resultado1.front() << endl;
            resultado1.pop();
        }
    }
    else{
        cout << "Nao existem transportes que partam as "<< horaPartida << ".\nNo entanto, estas sao as informacoes sobre os transportes cujas horas de partida sao as mais proximas das " << horaPartida << ":\n";
        if(resultado2.size()>0) {
            cout << endl << resultado2.top() << endl;
            resultado2.pop();
            if (resultado2.size() > 0)
                cout << endl << resultado2.top() << endl;
        }
    }
}

void Aeroporto::setArvoreTransporte() {
    ifstream inStream;
    string filename=nome + "Transporte.txt";
    inStream.open(filename);
    if(inStream.fail()){
        ofstream fout;
        fout.open(filename);
        fout.close();
        return;
    }
    string line;
    getline(inStream, line);
    while(getline(inStream, line))
    {
        string tipoTransporte, hora;
        double distanciaDoAeroporto;
        vector<std::string> horario;
        istringstream instr(line);
        instr >> tipoTransporte>> distanciaDoAeroporto;
        while(instr>>hora){
            horario.push_back(hora);
        }
        transportes.insert(LocalTransporteTerrestre(tipoTransporte, distanciaDoAeroporto, horario));
    }
    inStream.close();
}

void Aeroporto::printLocalTransporte(){
    transportes.printTree();
}

string Aeroporto::getNome() const{
    return nome;
}
