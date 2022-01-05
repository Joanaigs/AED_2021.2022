//
// Created by jigs2 on 08/12/2021.
//

#include "companhiaAerea.h"
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

double const tamanhoMaxBagagem = 158.0;  //em centimetros
double const pesoMaxBagagem = 32.0;      //em quilogramas

using namespace std;

void CompanhiaAerea::setAvioes(){
    avioes.clear();
    ifstream inStream;
    inStream.open("avioes.txt");
    if( inStream.fail( ) ) // OR if( !inStream.is_open( ) )
    {
        cout<<"o ficheiro nao existe\n";
        exit(0);
    }
    string line;
    getline(inStream, line);
    while(getline(inStream, line))
    {
        string matricula;
        unsigned int capacidade;
        istringstream instr(line);
        instr >> matricula >> capacidade;
        avioes.push_back(Aviao(matricula, capacidade));

    }
    inStream.close();

}

std::vector<Aviao> CompanhiaAerea::getAvioes() const{
    return avioes;
}

CompanhiaAerea::CompanhiaAerea() {}

bool CompanhiaAerea::comprarBilhete(bool &terminar) {
    for (auto aviao: avioes) {
        aviao.setPlanoVoo();
        aviao.mostrarPlanoVoo();
    }
    unsigned int nBilhetes;

    if (!util.getInput(nBilhetes, "Numero de bilhetes")){
        terminar=true;
        return false;
    }

    if (nBilhetes == 0) {
        cout << "Nao e possivel efetuar a compra de 0 bilhetes";
        return true;
    }

    while (nBilhetes > 0) {
        unsigned int numeroVoo;

        if (!util.getInput(numeroVoo, "Numero do voo"))
            return false;

        bool found = false;
        Voos voo=findVoo(numeroVoo, found);
        if (!found) {
            cout << "Numero de voo nao existe, tente novamente\n";
            return false;
        }
        if (voo.getLugaresDisponiveis() == 0) {
            cout << "Ja nao existem lugares disponiveis neste voo";
            return true;
        }
        string nome, dataNascimento;
        string tem, autom;
        bool bagagemAutomatica;
        bool temBagagem;
        cout << "Existe a possiblidade de comprar o bilhete. Que dados quer adicionar ao bilhete?\n"
                "Nome:";
        if (!util.getInputString(nome)){
            terminar=true;
            return false;
        }

        cout << "Data Nascimento:";
        if (!util.lerData(dataNascimento)){
            terminar=true;
            return false;
        }
        cout << "Tem bagagem(S/N)?";
        if (!util.getInputString(tem)){
            terminar=true;
            return false;
        }
        if (tem == "S" || tem == "s"){
            temBagagem = true;
            cout << "Bagagem automatica(S/N):";
            if (!util.getInputString(tem)){
                terminar=true;
                return false;
            }
            if (tem == "S" || tem == "s")
                bagagemAutomatica = true;
            else {
                bagagemAutomatica = false;
            }
        }
        else {
            temBagagem = false;
            bagagemAutomatica= false;
        }
        Bilhete bilhete(voo, temBagagem);
        Passageiro passageiro(nome, dataNascimento, bagagemAutomatica, bilhete);
        voo.setPassageiros();
        voo.adicionarPassageiro(passageiro);
        voo.updatePassageirosFile();
        nBilhetes--;
    }
    return true;
}

bool CompanhiaAerea::apagarBilhete(bool &terminar) {
    string nome, dataNascimento;
    unsigned int numeroVoo;
    if (!util.getInput(numeroVoo, "Inserir o numero de voo associado ao bilhete:"))
        return false;
    cout <<"Inserir o nome associado ao bilhete:";
    if (!util.getInputString(nome)){
        terminar=true;
        return false;
    }
    cout << "Inserir a data Nascimento: associado ao bilhete:";
    if (!util.lerData(dataNascimento)){
        terminar=true;
        return false;
    }
    bool found=false;
    Voos voo= findVoo(numeroVoo, terminar);
    voo.setPassageiros();
    vector<Passageiro> passageiros=voo.getPassageiros();
    vector<Passageiro>::iterator passageiro = find_if(passageiros.begin(), passageiros.end(), [&nome, &dataNascimento] (Passageiro &passageiro1){return passageiro1.getNome()==nome && passageiro1.getDataNascimento() == dataNascimento;});
    if(passageiro != passageiros.end()){
        found=true;
    }
    if(!found){
        cout<<"Nao esta registado/a neste voo, tente novamente";
        return false;
    }
    passageiros.erase(passageiro);
    voo.updatePassageiros(passageiros);
    return true;
}

void CompanhiaAerea::updateAvioesFile(){
    string filename="avioes.txt";
    ofstream fout (filename);
    fout << setw(15) << "Matricula:" << setw(15) << "Capacidade:";
    for(auto aviao:avioes){
        fout << "\n" << setw(15) << aviao.getMatricula() << setw(15) << aviao.getCapacidade();
    }
    fout.close();
}

void CompanhiaAerea::addAviao(const Aviao aviao){
    avioes.push_back(aviao);
    updateAvioesFile();
}

void CompanhiaAerea::mostrarAvioes() const{
    cout << setw(15) << "Matricula:" << setw(15) << "Capacidade:\n";
    for (Aviao aviao: avioes)
        cout << setw(15) << aviao.getMatricula() << setw(14) << aviao.getCapacidade() << "\n";
}

bool CompanhiaAerea::servicoLimpeza(bool &terminar) {
    mostrarAvioes();
    string matricula;
    cout<<"Introduza a matricula do aviao em que quer realizar o servico de limpeza:";
    if (!util.getInputString(matricula)){
        terminar=true;
        return false;
    }
    cout<<endl;
    vector<Aviao>::iterator aviao = find_if(avioes.begin(), avioes.end(), [&matricula](const Aviao &aviao){return aviao.getMatricula() == matricula;});
    aviao->setServicosPorRealizar();
    aviao->setServicosRealizados();
    if(!aviao->realizarServico()){
        cout<<"Nao existe mais servicos por realizar\n";
        return true;
    }
    cout<<"Servico de limpeza feito, os dados foram atualizados\n";
    return true;
}

bool CompanhiaAerea::adicionarServico(bool &terminar) {
    mostrarAvioes();
    cout << "\n";

    string matricula;
    cout << "Escolha a matricula do aviao a que quer adicionar o servico:";
    if (!util.getInputString(matricula)){
        terminar=true;
        return false;
    }
    cout << "\n";
    for (auto aviao: getAvioes()) {
        aviao.setServicosPorRealizar();
        aviao.setServicosRealizados();
        if (aviao.getMatricula() == matricula) {
            while (true) {
                if (aviao.adicionarServico()) {
                    return true;
                }
                else {
                    cout << "Nao foi possivel adicionar servico nessa data, por favor tente novamente\n";
                }

            }
        }
    }
    cout << "O aviao nao existe\n";
    return false;
}

bool CompanhiaAerea::adicionarVoo(bool &terminar) {

    mostrarAvioes();
    cout<<"\n";
    string matricula;
    cout << "Escolha a matricula do aviao a que quer adicionar o voo:";
    if (!util.getInputString(matricula)){
        terminar=true;
        return false;
    }
    for (auto aviao: getAvioes()) {
        aviao.setPlanoVoo();
        if (aviao.getMatricula() == matricula) {
            while (true) {
                if (aviao.adicionarVoo(terminar)) {
                    return true;
                }
                else {
                    cout<<"O numero de voo ja existe, por favor tente novamente\n";
                }
            }
        }
    }
    cout << "O aviao nao existe\n";
    return false;
}

Aviao CompanhiaAerea::findAviao(const string &matricula, bool &found) {
    Aviao aviao;
    vector<Aviao>::iterator it = find_if(avioes.begin(), avioes.end(), [&matricula](const Aviao &a){return a.getMatricula() == matricula;});
    if(it!=avioes.end()){
        found = true;
        aviao = *it;
    }
    return aviao;
}

Voos CompanhiaAerea::findVoo(int numeroVoo, bool &found) {
    Voos voo;
    for (auto aviao: avioes) {
        aviao.setPlanoVoo();
        list<Voos> planoVoo = aviao.getPlanoVoo();
        list<Voos>::iterator vooPretendido;
        vooPretendido = find_if(planoVoo.begin(), planoVoo.end(),
                                [&numeroVoo](Voos &voo) { return numeroVoo == voo.getNumeroVoo(); });
        if (vooPretendido != planoVoo.end()) {
            found = true;
            voo=*vooPretendido;
            break;
        }
    }
    return voo;
}

vector<Voos> CompanhiaAerea::findVoos(const string &info, bool &found) {
    vector<Voos> voos_destino;
    vector<Voos> voos_data;

    for (auto aviao: avioes) {
        aviao.setPlanoVoo();
        list<Voos> planoVoo = aviao.getPlanoVoo();
        list<Voos>::iterator voo_info;
        if(info.find("-")!=string::npos) {
            voo_info = find_if(planoVoo.begin(), planoVoo.end(),
                                  [&info](Voos &voo) { return info == voo.getDestino(); });
            if (voo_info != planoVoo.end()) {
                found = true;
                voos_destino.push_back(*voo_info);
            }
        }
        else {
            voo_info = find_if(planoVoo.begin(), planoVoo.end(),
                               [&info](Voos &voo) { return info == voo.getDataPartida(); });

            if (voo_info != planoVoo.end()) {
                found = true;
                voos_data.push_back(*voo_info);
            }
        }
    }

    if(info.find("-")!=string::npos)
        return voos_destino;
    else
        return voos_data;
}

bool CompanhiaAerea::getAeroporto(Aeroporto aeroporto, bool &terminar) {
    cout << "Introduza o nome do aeroporto sobre o qual quer saber as informaçoes de transporte:\n";
    string nomeAeroporto;
    if(!util.getInputString(nomeAeroporto)){
        terminar=true;
        return false;
    }
    bool found = false;
    setAvioes();
    for (auto aviao: getAvioes()) {
        aviao.setPlanoVoo();
        list<Voos> temp = aviao.getPlanoVoo();
        list<Voos>::iterator vooPretendido;
        vooPretendido = find_if(temp.begin(), temp.end(), [&nomeAeroporto](Voos &voo) {
            return (voo.getAeroportoPartida()->getNome() == nomeAeroporto) ||
                   (voo.getAeroportoChegada()->getNome() == nomeAeroporto);
        });
        if (vooPretendido != temp.end()) {
            if(vooPretendido->getOrigem() == nomeAeroporto)
                aeroporto = *(vooPretendido->getAeroportoPartida());
            else
                aeroporto = *(vooPretendido->getAeroportoChegada());
            found = true;
            break;
        }
    }
    if(found)
        return true;
    else{
        cout << "\nNao temos informacoes sobre esse aeroporto. Tente novamente\n";
        return false;
    }
}

bool CompanhiaAerea::eliminarVoo(bool &terminar) {

    bool anotherOperation = true;
    unsigned int numeroVoo;

    while (anotherOperation) {
        for (auto aviao: getAvioes()) {
            aviao.setPlanoVoo();
            aviao.mostrarPlanoVoo();
        }
        if(!util.getInput(numeroVoo, "\nNumero identificador do voo a eliminar:")){
            terminar = true;
            return false;
        }
        for (auto aviao: avioes) {
            aviao.setPlanoVoo();
            list<Voos> planoVoo = aviao.getPlanoVoo();
            if(planoVoo.size()>0){
                list<Voos>::iterator vooPretendido;
                vooPretendido = find_if(planoVoo.begin(), planoVoo.end(),
                                        [&numeroVoo](Voos &voo) { return numeroVoo == voo.getNumeroVoo(); });
                if (vooPretendido != planoVoo.end()) {
                    aviao.apagarVoo(numeroVoo);
                    break;
                }
            }
            else {
                cout<< "Nao existe nenhum voo com esse numero identificador\n";
                break;
            }
        }
        cout<<"Quer eliminar mais um voo?(S/N)";
        char temp;
        cin>>temp;
        if(temp=='N'||temp=='n')
            anotherOperation=false;
    }
    return true;
}

bool CompanhiaAerea::checkIn(bool &terminar) {
    bool found1=false;
    bool found2=false;
    unsigned int numeroVoo;
    string nome, dataNascimento;

    if(!util.getInput(numeroVoo, "Qual e o numero do seu voo?"))
        return false;

    cout << "Introduza o seu nome";
    if(!util.getInputString(nome))
        return false;
    cout << "Introduza a sua data de nascimento";
    getline(cin, dataNascimento);

    if (!util.lerData(dataNascimento)){
        terminar=true;
        return false;
    }

    vector<Passageiro>::iterator passageiro;
    Voos voo = findVoo(numeroVoo, found2);

    voo.setPassageiros();
    vector<Passageiro> temp = voo.getPassageiros();
    passageiro = find_if(temp.begin(), temp.end(), [&nome, &dataNascimento] (Passageiro &passageiro1){return passageiro1.getNome()==nome && passageiro1.getDataNascimento() == dataNascimento;});
    if(passageiro != temp.end()){
        found1=true;
    }

    if(!found1){
        cout<<"Nao esta registado/a neste voo, tente novamente";
        return false;
    }

    string tem;
    unsigned n;
    double peso, tamanho;
    cout << "Tem bagagem (S/s ou N/n)?";
    if(!util.getInputString(tem))
        return false;

    if(tem == "N" || tem == "n"){
        return true;
    }
    if(!util.getInput(n, "Quantas tem?"))
        return false;
    while(n>0) {
        if(!util.getInput(peso,  "Qual e o peso da sua mala? (introduza em kilogramas)"))
            return false;
        if (peso > pesoMaxBagagem) {
            cout << "A sua bagagem nao e aceite porque excede os limites de peso";
            return true;
        }
        cout << "Qual e o tamanho da sua mala? (introduza em centimetros)";
        cin >> tamanho;
        if(!util.getInput(tamanho,  "Qual e o tamanho da sua mala? (introduza em centimetros)"))
            return false;
        if (tamanho > tamanhoMaxBagagem) {
            cout << "A sua bagagem nao e aceite porque excede os limites de tamanho";
            return true;
        }
        Bagagem bagagem(nome, peso, tamanho);
        voo.setBagagens();
        if (!voo.adicionarBagagem(bagagem)) {
            return true;
        }
        n--;
        voo.updateBagagemFile();
    }
    return true;
}

bool CompanhiaAerea::adicionarAviao(bool &terminar) {
    unsigned capacidade;
    string matricula;
    cout << "Insira a matricula do aviao que pretende adicionar:";
    if (!util.getInputString(matricula)){
        terminar=true;
        return false;
    }
    vector<Aviao> avioes=getAvioes();
    auto a = find_if(avioes.begin(), avioes.end(), [&matricula](const Aviao &aviao){return aviao.getMatricula()==matricula;});
    if(a != avioes.end()){
        cout<<"O aviao da matricula dada ja existe\n";
        return true;
    }

    if (!util.getInput(capacidade, "Insira a capacidade do aviao: ")){
        return false;
    }
    Aviao aviao(matricula, capacidade);
    addAviao(aviao);
    updateAvioesFile();
    return true;
}



