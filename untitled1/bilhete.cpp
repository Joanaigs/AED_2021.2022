#include "bilhete.h"


using namespace std;


Bilhete::Bilhete(Voos voo, bool temBagagem) {
    this->voo = &voo;
    this->temBagagem = temBagagem;

}