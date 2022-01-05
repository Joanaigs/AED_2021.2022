#ifndef AED_PROJ1_2021_SERVICO_H
#define AED_PROJ1_2021_SERVICO_H
#include <string>

class Servico{
public:
    Servico(std::string data, std::string tipoServico, std::string fucionario);
    std::string getData();
    std::string getTipoServico();
    std::string getFuncionario();
    void mostrarServico();
    
private:
    std::string data, tipoServico, funcionario;


};

#endif //AED_PROJ1_2021_SERVICO_H
