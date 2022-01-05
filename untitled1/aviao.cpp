#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "aviao.h"
using namespace std;
static Uteis util;
Aviao::Aviao() = default;

Aviao::Aviao(string matricula, unsigned int capacidade) :matricula(std::move(matricula)), capacidade(capacidade){}

void clear(std::queue<Servico> &q )
{
    while (!q.empty())
    {
        q.pop();
    }
}

void Aviao::setServicosPorRealizar() {
    clear(servicosPorRealizar);
    ifstream inStream;
    string filename=matricula+"ServicosPorRealizar.txt";
    inStream.open(filename);
    if(inStream.fail( ) ) // OR if( !inStream.is_open( ) )
    {
        cerr << "Input file opening failed.\n";
        exit(1) ;
    }
    string line;
    getline(inStream, line);
    while(getline(inStream, line))
    {
        string data, tipoServico, funcionario;
        istringstream instr(line);
        instr >> funcionario>> tipoServico>> data;
        Servico servico(data, tipoServico, funcionario);
        servicosPorRealizar.push(servico);
    }
    inStream.close();
}

void Aviao::setServicosRealizados() {
    clear(servicosRealizados);
    ifstream inStream;
    string filename=matricula+"ServicosRealizados.txt";
    inStream.open(filename);
    if(inStream.fail( ) ) // OR if( !inStream.is_open( ) )
    {
        cerr << "Input file opening failed.\n";
        exit(1) ; // sometimes, it is best to stop the program, // with an exit code != 0
    }
    string line;
    getline(inStream, line);
    while(getline(inStream, line))
    {
        string data, tipoServico, funcionario;
        istringstream instr(line);
        instr >> funcionario>> tipoServico>> data;
        Servico servico(data, tipoServico, funcionario);
        servicosRealizados.push(servico);
    }
    inStream.close();
}

void Aviao::setPlanoVoo() {
    planoVoo.clear();
    string filename = matricula + "planoVoo.txt";
    ifstream inStream;
    inStream.open(filename);
    if( inStream.fail( ) ) // OR if( !inStream.is_open( ) )
    {
        cerr << "Input file opening failed.\n";
        exit(1) ; // sometimes, it is best to stop the program, // with an exit code != 0
    }
    string line;
    getline(inStream, line);
    while(getline(inStream, line))
    {
        int numeroVoo=0, lugaresDisponiveis=0;
        double duracaoVoo=0.0, preco=0.0;
        string dataPartida="" ,origem="", destino="";
        istringstream instr(line);
        instr>>numeroVoo>>duracaoVoo>>dataPartida>>origem>>destino>>preco>>lugaresDisponiveis;
        Voos voo(numeroVoo, duracaoVoo, dataPartida, origem, destino, preco, lugaresDisponiveis);
        planoVoo.push_back(voo);
    }

    inStream.close();
}

queue<Servico> Aviao::getServicosPorRealizar() const{
    return servicosPorRealizar;
}

queue<Servico> Aviao::getServicosRealizados() const{
    return servicosRealizados;
}

unsigned Aviao::getCapacidade() const{
    return capacidade;
}

void Aviao::updateServicosFile(const string& filename, queue<Servico> servicos){
    queue<Servico> copiaTemp = servicos;
    ofstream fout (filename);
    fout << setw(20) << "id funcionario" << setw(25) << "tipoServico" << setw(20) << "data" ;
    for(int i=0; i< servicos.size();i++) {
        fout<<'\n' << setw(20) << (copiaTemp.front()).getFuncionario() << setw(25) << (copiaTemp.front()).getTipoServico()
            << setw(20) << (copiaTemp.front()).getData();
        copiaTemp.pop();
    }
    fout.close();
}

bool Aviao::realizarServico(){
    if(servicosPorRealizar.size()==0)
        return false;
    servicosRealizados.push(servicosPorRealizar.front());
    servicosPorRealizar.pop();
    string filename1=matricula+"ServicosPorRealizar.txt", filename2=matricula+"ServicosRealizados.txt";
    updateServicosFile(filename1, servicosPorRealizar);
    updateServicosFile(filename2, servicosRealizados);
    return true;
}

void Aviao::mostrarServicos() {
    cout<<"Servicos Por Realizar: \n";
    cout  << setw(20) << "id Funcionario"  << setw(20) << "Tipo de Servico"  << setw(20) << "Data\n" ;
    int n=servicosPorRealizar.size();
    for(int i=0; i<n;i++){
        Servico temp=servicosPorRealizar.front();
        temp.mostrarServico();
        servicosPorRealizar.pop();
    }
    cout << endl;
    cout<<"Servicos Realizados: \n";
    cout  << setw(20) << "id Funcionario"  << setw(20) << "Tipo de Servico"  << setw(20) << "Data\n" ;
    n=servicosRealizados.size();
    for(int i=0; i<n;i++){
        Servico temp=servicosRealizados.front();
        temp.mostrarServico();
        servicosRealizados.pop();
    }

}

void Aviao::mostrarPlanoVoo(){
    cout << "Voos : \n";
    cout <<setw(15) << "Numero do Voo"<< setw(20) << "Data de Partida" << setw(15) << "Partida" << setw(15) << "Destino"  << setw(20) << "Duracao do voo" <<setw(10)<< "Preco" << setw(20) << "Lugares Disponiveis\n";
    list<Voos>::iterator it = planoVoo.begin();
    list<Voos>::iterator iter = planoVoo.end();
    while(it!=iter) {
        it->mostrarInfoVoo();
        it++;
    }

}

std::string Aviao::getMatricula() const {
    return matricula;
}

bool Aviao::adicionarServico() {
     setServicosPorRealizar();
     bool anotherOperation = true;
     string data, tipoServico, funcionario;
     while (anotherOperation) {
         cout << "-Adicionar Servico:\n";

         if (!util.lerData(data))
             return true;

         unsigned ano1, mes1, dia1, ano2, mes2, dia2;
         char ch;
         string data2;
         if(servicosPorRealizar.size()>0) {
            data2=servicosPorRealizar.back().getData();
         }
         else{
             data2=servicosRealizados.back().getData();
         }
         istringstream instr2(data2);
         istringstream instr1(data);
         instr1 >> dia1 >> ch >> mes1 >> ch >> ano1;
         instr2 >> dia2 >> ch >> mes2 >> ch >> ano2;
         if ((ano1 < ano2) && (mes1 < mes2) && (dia1 < dia2)) {
             cout << "Data indisponivel."<<endl;
             return false;
         }

         cout << "Tipo de Servico:";
         cin >> tipoServico;
         cout << "id de funcionario:";
         cin >> funcionario;
         Servico servico(data, tipoServico, funcionario);
         servicosPorRealizar.push(servico);
         string filename1=matricula+"ServicosPorRealizar.txt";
         updateServicosFile(filename1, servicosPorRealizar);
         cout<<"Quer adicionar mais um servico?(S/N)";
         char temp;
         cin>>temp;
         if(temp=='N'||temp=='n')
             anotherOperation=false;
     }
     return true;
 }

void Aviao::apagarVoo(unsigned int numeroVoo) {
    setPlanoVoo();
    list<Voos>::iterator vooPretendido;
    vooPretendido = find_if(planoVoo.begin(), planoVoo.end(),
                            [&numeroVoo](Voos &voo) { return numeroVoo == voo.getNumeroVoo(); });

    if (vooPretendido != planoVoo.end()) {
        planoVoo.erase(vooPretendido);
        string filename=matricula+"planoVoo.txt";
        updatePlanoVooFile(filename);
    }
}

bool Aviao::adicionarVoo(bool &terminar){
    bool anotherOperation = true;

    unsigned int numeroVoo;
    double duracaoVoo, preco;
    string dataPartida, origem, destino;

    while (anotherOperation) {
        cout << "-Adicionar Voo:\n";
        cout << "Numero do voo:";
        cin >> numeroVoo;
        list<Voos>::iterator it=planoVoo.begin();
        for(it; it!=planoVoo.end();it++){
            if(it->getNumeroVoo()==numeroVoo)
                return false;
        }
        if(!util.getInput(duracaoVoo,  "Duracao do voo:")){
            terminar=true;
            return true;
        }
        cout << "Data de partida:";

        if(!util.lerData(dataPartida)){
            terminar=true;
            return true;
        }
        cout << "Local de partida:";
        if(!util.getInputString(origem)){
            terminar=true;
            return true;
        }
        cout << "Destino:";
        if(!util.getInputString(destino)){
            terminar=true;
            return true;
        }
        if(!util.getInput(preco,  "Preco do voo:")){
            terminar=true;
            return true;
        }
        Voos voo(numeroVoo, duracaoVoo, dataPartida, origem, destino, preco, capacidade);
        planoVoo.push_back(voo);
        string filename=matricula+"planoVoo.txt";
        updatePlanoVooFile(filename);
        cout<<"Quer adicionar mais um voo?(S/N)";
        char temp;
        cin>>temp;
        if(temp=='N'||temp=='n')
            anotherOperation=false;
    }
    return true;
}

void Aviao::updatePlanoVooFile(string filename){
    ofstream fout (filename);
    fout <<setw(20)<< "numeroVoo" << setw(20) << "duracaoVoo" << setw(20) << "dataPartida" << setw(20) << "origem" << setw(20) << "destino" << setw(15) << "preço" <<setw(25)<<"lugaresDisponiveis";
    list<Voos>::iterator it = planoVoo.begin();
    list<Voos>::iterator iter = planoVoo.end();
    while(it!=iter) {
        fout << '\n' <<setw(20)<< it->getNumeroVoo() << setw(20) << it->getDuracaoVoo() << setw(20)
             << it->getDataPartida() << setw(20) << it->getOrigem() <<setw(20)<< it->getDestino() << setw(15) << it->getPreco()<<setw(25) << it->getLugaresDisponiveis();
        it++;
    }
    fout.close();
}

list<Voos> Aviao::getPlanoVoo() const{
    return planoVoo;
}

void Aviao::updatePlanoVoo(list<Voos> planoVoo){
    this->planoVoo = planoVoo;
}




