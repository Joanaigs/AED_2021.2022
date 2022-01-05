#include "voos.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

Voos::Voos() {
}

Voos::Voos(unsigned int numeroVoo, double duracaoVoo, std::string dataPartida, string origem, string destino, double preco, unsigned lugaresDisponiveis) {
    this->numeroVoo = numeroVoo;
    this->duracaoVoo = duracaoVoo;
    this->dataPartida = dataPartida;
    this->aeroportoPartida = new Aeroporto(origem);
    this->aeroportoChegada = new Aeroporto(destino);
    this->preco = preco;
    this->lugaresDisponiveis = lugaresDisponiveis;
    this->carrinhoTransporte = std::vector<std::vector<std::stack<Bagagem>>>(0, std::vector<std::stack<Bagagem>>(0, std::stack<Bagagem>()));
}


unsigned int Voos::getNumeroVoo(){
    return numeroVoo;
}

double Voos::getDuracaoVoo(){
    return duracaoVoo;
}

string Voos::getDataPartida(){
    return dataPartida;
}

double Voos::getPreco(){
    return preco;
}


void Voos::mostrarInfoVoo() {
    cout << setw(15) << numeroVoo << setw(20) << dataPartida << setw(20) << aeroportoPartida->getNome() << setw(20) << aeroportoChegada->getNome() << setw(25) << duracaoVoo << setw(10) << preco << setw(25) << lugaresDisponiveis <<endl;
}

unsigned Voos::getLugaresDisponiveis() {
    return lugaresDisponiveis;
}

void Voos::setPassageiros(){
    passageirosVoo.clear();
    string filename = to_string(numeroVoo) + "Passageiros.txt";
    ifstream inStream;
    inStream.open(filename);
    if( inStream.fail( ) ) // OR if( !inStream.is_open( ) )
    {
        ofstream fout;
        fout.open(filename);
        fout.close();
        return; // sometimes, it is best to stop the program, // with an exit code != 0
    }
    string line;
    getline(inStream, line);
    while(getline(inStream, line))
    {
        string nome ,dataNascimento;
        float peso, tamanho;
        bool bagagemAutomatica;
        istringstream instr(line);
        instr >> nome >> dataNascimento >> bagagemAutomatica;
        Passageiro pessoa(nome, dataNascimento, bagagemAutomatica);
        passageirosVoo.push_back(pessoa);
    }
    inStream.close();
}

vector<Passageiro> Voos::getPassageiros(){
    return passageirosVoo;
}

void Voos::updatePassageirosFile(){
    string filename=to_string(numeroVoo)+"Passageiros.txt";
    ofstream fout (filename);
    fout << "nome" << setw(20) << "dataNascimento" << setw(20) << "bagagemAutomática";

    for( unsigned i=0; i< passageirosVoo.size(); i++){
        fout << '\n' <<setw(10)<< passageirosVoo[i].getNome() << setw(17) << passageirosVoo[i].getDataNascimento() << setw(20)
             << passageirosVoo[i].getBagagemAutomatica();
    }
    fout.close();
}

void Voos::adicionarPassageiro(Passageiro passageiro) {
    passageirosVoo.push_back(passageiro);
    lugaresDisponiveis--;
}

void Voos::showPassageirosVoo() {
    cout<<"Passageiros: \n";
    cout  << "nome" << setw(20) << "dataNascimento" << setw(20) << "bagagemAutomática\n";
    for(auto pessoa: passageirosVoo){
        pessoa.mostrarPassageiro();
    }
}

void Voos::setBagagens() {
    carrinhoTransporte.clear();
    string filename = to_string(numeroVoo)+"Bagagem.txt";
    ifstream inStream;
    inStream.open(filename);
    if( inStream.fail( ) ) // OR if( !inStream.is_open( ) )
    {
        ofstream fout;
        fout.open(filename);
        fout.close();
        return;
    }
    string line;
    getline(inStream, line);
    while(getline(inStream, line))
    {
        double peso, tamanho;
        string nome;
        istringstream instr(line);
        instr >>nome>> peso>>tamanho;
        Bagagem bagagem(nome, peso, tamanho);
        if(!adicionarBagagem(bagagem))
            break;
    }
    inStream.close();
}

bool Voos::adicionarBagagem(Bagagem bagagem){
    //std::vector<std::vector<std::stack<Bagagem>>> carrinhoTransporte;
    for(auto &carruagem:carrinhoTransporte){
        for(auto &pilha:carruagem){
            if(pilha.size()<numMaxMalas){
                pilha.push(bagagem);
                return true;
            }
            if(carruagem.size()<numPilhasPorCarruagem) {
                stack<Bagagem> temp;
                temp.push(bagagem);
                carruagem.push_back(temp);
                return true;
            }
        }
    }
    if(carrinhoTransporte.size()<numCarruagensCarrinhoTransporte) {
        stack<Bagagem> temp;
        temp.push(bagagem);
        vector<stack<Bagagem>> temp2;
        temp2.push_back(temp);
        carrinhoTransporte.push_back(temp2);
        return true;
    }
    return false;
}

bool Voos::operator==(Voos voo2) const{
    return (numeroVoo==voo2.getNumeroVoo());
}

std::vector<std::vector<std::stack<Bagagem>>> Voos::getCarrinhoTransporte(){
    return carrinhoTransporte;
}

void Voos::updateBagagemFile(){
    string filename=to_string(numeroVoo)+"Bagagem.txt";
    ofstream fout (filename);
    fout << setw(20) << "nome" << setw(20) << "bagagem";
    for(const auto& carruagem : carrinhoTransporte){
        for(const auto& pilha: carruagem){
            stack<Bagagem> temp(pilha) ;
            while(!temp.empty()){
                fout << '\n' <<setw(20) << temp.top().getNomePassageiro() << setw(20) << temp.top().getPeso() << " " << temp.top().getTamanho();
                temp.pop();
            }
        }
    }
    fout.close();
}

std::string Voos::getOrigem() {
    return aeroportoPartida->getNome();
}

std::string Voos::getDestino() {
    return aeroportoChegada->getNome();
}

Aeroporto *Voos::getAeroportoPartida() const{
    return aeroportoPartida;
}

Aeroporto *Voos::getAeroportoChegada() const{
    return aeroportoChegada;
}

void Voos::updatePassageiros(std::vector<Passageiro> passageirosVoo) {
    this->passageirosVoo=passageirosVoo;
}
