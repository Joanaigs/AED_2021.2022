// AED 2021/2022 - Aula Pratica 08
// Pedro Ribeiro (DCC/FCUP) [12/12/2021]

#include "funWithHashTables.h"
#include "hashTable.h"

#include <vector>
#include <iostream>
#include <cctype>

// Exemplo de função de hash para ints
unsigned FunWithHashTables::hashInt(const int& i) {
  return i;
}

// Exemplo de função de hash para strings
unsigned FunWithHashTables::hashString(const string& s) {
  hash<string> h;
  return h(s);
}

// ----------------------------------------------------------
// Exercicio 1: Tabelas de Dispersão
// ----------------------------------------------------------

// ..............................
// d) Contando diferentes somas de pares
// TODO
int FunWithHashTables::sumPairs(const vector<int>& numbers) {
  int s=numbers.size();
  HashTable<int> table(s*s, hashInt);
  for(int i=0;i<s; i++ ){
      for(int j=i+1; j<s; j++)
          table.insert(numbers[i]+numbers[j]);
  }
  return table.getNumActive();
}

// ----------------------------------------------------------
// Exercicio 2: Um padrão no DNA
// ----------------------------------------------------------
// TODO
int FunWithHashTables::dnaMotifs(string dna, int k, unordered_set<string>& motifs) {
    unordered_map<string, int> result;
    for(int i = 0; i < dna.size() - k + 1 ;i++){
        string motif = dna.substr(i, k);
        if(result.find(motif) != result.end()){
            result[motif] += 1;
        }
        else{
            result.insert({motif,1});
        }
    }
    int m = 0;
    for(auto it = result.begin();it != result.end(); it++){
        m = max(m, (*it).second);
    }
    for(auto it = result.begin();it != result.end(); it++){
        if ((*it).second == m){
            motifs.insert((*it).first);
        }
    }
    return m;
}

// ----------------------------------------------------------
// Exercicio 3: Torre de Babel
// ----------------------------------------------------------
// TODO
void FunWithHashTables::findLanguage(string text, const unordered_map<string, vector<string>>& dict, unordered_map<string, int>& answer) {
}

// ----------------------------------------------------------
// Exercicio 4: Palavras Alienígenas
// ----------------------------------------------------------
// TODO
void FunWithHashTables::wordIndex(const vector<string> &words, vector<int>& answer) {
}
