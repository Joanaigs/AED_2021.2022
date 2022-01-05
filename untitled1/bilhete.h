#ifndef AED_PROJ1_2021_BILHETE_H
#define AED_PROJ1_2021_BILHETE_H

#include "voos.h"
#include "bagagem.h"
#include <vector>

class Voos;
class Bilhete{
public:
    Bilhete(Voos voo, bool temBagagem);


private:
    Voos *voo;
    bool temBagagem;
};

#endif //AED_PROJ1_2021_BILHETE_H
