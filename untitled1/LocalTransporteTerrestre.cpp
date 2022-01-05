//
// Created by jigs2 on 01/12/2021.
//
#include "LocalTransporteTerrestre.h"
#include <string>
using namespace std;

LocalTransporteTerrestre::LocalTransporteTerrestre(const std::string &tipoTransporte, const double distanciaDoAeroporto, vector<string> horario){
    this->tipoTransporte = tipoTransporte;
    this->distanciaDoAeroporto = distanciaDoAeroporto;
    this->horario = horario;
}

string LocalTransporteTerrestre::getTipoTransporte() const{
    return tipoTransporte;
}

double LocalTransporteTerrestre::getDistanciaDoAeroporto() const {
    return distanciaDoAeroporto;
}

vector<string> LocalTransporteTerrestre::getHorario() const{
    return horario;
}

bool LocalTransporteTerrestre::operator<(const LocalTransporteTerrestre &t1) const {
    return (distanciaDoAeroporto < t1.getDistanciaDoAeroporto());
}

bool LocalTransporteTerrestre::operator==(const LocalTransporteTerrestre &t1) const{
    return (tipoTransporte == t1.getTipoTransporte() && distanciaDoAeroporto == t1.getDistanciaDoAeroporto());
}

std::ostream& operator<<(std::ostream& out, const LocalTransporteTerrestre& local){
    out <<"Tipo de Transporte: " <<local.getTipoTransporte() <<  endl << "Distancia ao aeroporto: " <<  local.getDistanciaDoAeroporto() << endl;
    out << "Horarios: " << endl;
    for(auto& hora: local.getHorario()){
        out << hora << " ";
    }
    return out;
}