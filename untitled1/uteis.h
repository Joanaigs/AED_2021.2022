//
// Created by jigs2 on 07/12/2021.
//

#ifndef AED_PROJ1_2021_UTEIS_H
#define AED_PROJ1_2021_UTEIS_H
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

class Uteis {
public:
    void normalizarInput(string &input) {
        size_t i = 0;
/*
        if(isalpha(input.at(i)))
            input.at(i) = toupper(input.at(i));
*/
        while (i < input.length()) {
            char &c = input.at(i);
            if (c == '\t')
                c = ' ';
            if (c == ' ') {
                /*
                if(i+1< input.length()){
                    if(int(input.at(i+1))>=97 && int(input.at(i+1))<=122)
                        input.at(i+1) = toupper(input.at(i+1));
                }
                 */
                input.erase(i, 1);
                if (i == input.length())
                    i--;
            }

            else {
                i++;
            }
        }
    }

    bool getInputString(string &input) {
        getline(cin, input);
        normalizarInput(input);
        if (cin.eof())
            return false;

        return true;
    }

    template<class T>
    bool getInput(T &input, string frase) {
        bool validOperands;
        do {
            validOperands = true;
            cout << frase;
            cin >> input;
            if (cin.fail()) {
                validOperands = false;
                if (cin.eof()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    return false;
                }
                cin.clear();
                cin.ignore(10000, '\n');
            }
            else cin.ignore(10000, '\n');
        } while (!validOperands);
        return true;
    }

    bool dataExiste(int dia, int mes, int ano){      // Verificar se a data existe
        if ((dia >= 1 and dia <= 31) and (mes >= 1 && mes <= 12)){
            if ((dia == 29 and mes == 2) && ((ano % 4) == 0)) //verifica se o ano e bissexto
            {
                return true;
            }
            else if (dia <= 28 and mes == 2) //verifica o mes de feveireiro
            {
                return true;
            }
            else if ((dia <= 30) and (mes == 4 or mes == 6 or mes == 9 or mes == 11)) //verifica os meses de 30 dias
            {
                return true;
            }
            else if ((dia <= 31) and (mes == 1 or mes == 3 or mes == 5 or mes == 7 or mes ==8 or mes == 10 or mes == 12)) //verifica os meses de 31 dias
            {
                return true;
            }
            return false;
        }
        return false;
    }

    bool verificaData(string &data){
        int traco1 = data.find('-', 0);
        int traco2 = data.find('-', traco1 + 1);

        if( traco1== string::npos or traco2 == string::npos){
            return false;
        }

        string d = data.substr(0, traco1);
        string m = data.substr(traco1 + 1, traco2);
        string y = data.substr(traco2 + 1);

        int dia = stoi(d);
        int mes = stoi(m);
        int ano = stoi(y);

        // Normalizar as estrutura das datas de forma a ficarem todas com a mesma estrutura
        stringstream ss;
        ss << setfill ('0') <<  setw (2) << dia   << "-" << setfill ('0') <<  setw (2) << mes << "-" << ano;
        data = ss.str();

        if(dataExiste(dia, mes, ano))
            return true;
        else
            return false;
    }

    bool lerData(string &data) {
        bool valida = verificaData(data);
        if (!valida) {
            do {
                cout << "\nPor favor, insira uma data valida. Escreva no formato DD-MM-YYYY" << endl;
                cin >> data;
                if (cin.fail()) {
                    if (cin.eof()) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        return false;
                    }
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                else cin.ignore(10000, '\n');
            } while (!verificaData(data));
        }
        return true;
    }

};
#endif //AED_PROJ1_2021_UTEIS_H
