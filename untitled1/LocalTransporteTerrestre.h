//
// Created by jigs2 on 01/12/2021.
//

#ifndef AED_PROJ1_2021_LOCALTRANSPORTETERRESTRE_H
#define AED_PROJ1_2021_LOCALTRANSPORTETERRESTRE_H


#include <string>
#include <list>
#include <vector>
#include <iostream>

class LocalTransporteTerrestre {
public:
    LocalTransporteTerrestre(const std::string &tipoTransporte, const double distanciaDoAeroporto, const std::vector<std::string> horario);
    std::string getTipoTransporte() const;
    double getDistanciaDoAeroporto() const;
    std::vector<std::string> getHorario() const;
    bool operator < (const LocalTransporteTerrestre &t1) const;
    bool operator == (const LocalTransporteTerrestre &t1) const;
    friend std::ostream& operator<<(std::ostream& out, const LocalTransporteTerrestre& local);
private:
    std::string tipoTransporte;
    double distanciaDoAeroporto;
    std::vector<std::string> horario;
};

#endif //AED_PROJ1_2021_LOCALTRANSPORTETERRESTRE_H
