#include "parque.h"
#include <vector>

using namespace std;


ParqueEstacionamento::ParqueEstacionamento(unsigned lot, unsigned nMaxCli)
        :lotacao(lot), numMaximoClientes(nMaxCli) {
    vagas=lotacao;
}

unsigned ParqueEstacionamento::getNumLugares() const
{
    return lotacao;
}

unsigned ParqueEstacionamento::getNumMaximoClientes() const
{
    return numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const string & nome) const
{
    for (int i=0; i<clientes.size(); i++)
    {
        if(clientes[i].nome==nome)
            return i;
    }
    return -1;
}

bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
    InfoCartao card;
    card.nome=nome;
    card.presente=false;
    if(clientes.size()+1<=numMaximoClientes) {
        clientes.push_back(card);
        return true;
    }
    return false;
}

bool ParqueEstacionamento::entrar(const string & nome)
{
    if(vagas==0) return false;
    for(int i=0; i<clientes.size();i++)
    {
        if(clientes[i].nome==nome) {
            if(clientes[i].presente) {
                return false;
            }
            else{
                clientes[i].presente=true;
                vagas--;
                return true;
            }
        }
    }
    return false;
}
bool ParqueEstacionamento::retiraCliente(const string & nome)
{
    for (int i=0; i<clientes.size();i++)
    {
        if(clientes[i].nome==nome)
        {
            if(clientes[i].presente==false) {
                clientes.erase(clientes.begin() + i);
                return true;
            }
        }
    }
    return false;
}

bool ParqueEstacionamento::sair(const string & nome)
{
    for(int i=0; i<clientes.size();i++)
    {
        if(clientes[i].nome==nome) {
            if(clientes[i].presente) {
                clientes[i].presente=false;
                vagas++;
                return true;
            }
            return false;
        }
    }
    return false;
}

unsigned ParqueEstacionamento::getNumLugaresOcupados() const{
    return lotacao-vagas;
}
unsigned ParqueEstacionamento::getNumClientesAtuais() const
{
    return clientes.size();
}