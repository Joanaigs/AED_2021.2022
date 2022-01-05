// AED 2021/2022 - Aula Pratica 07
// Pedro Ribeiro (DCC/FCUP) [06/12/2012]

#include "funWithBSTs.h"
#include <set>
#include <map>
#include "bst.h"
#include <algorithm>

// ----------------------------------------------------------
// Exercicio 1: Colecao de Cromos
// ----------------------------------------------------------
// TODO
int FunWithBSTs::newBag(const vector<int>& collection, const vector<int>& bag) {
  set<int> temp;
  for(auto cart:collection)
      temp.insert(cart);
  int aux=temp.size();
  for(auto cart:bag)
      temp.insert(cart);
  return temp.size()-aux;
}

// ----------------------------------------------------------
// Exercicio 2: Batalha de Pokemons
// ----------------------------------------------------------
// TODO
bool cmp(int i, int j){
    return i>j;
}


int FunWithBSTs::battle(const vector<int>& alice, const vector<int>& bruno) {
  multiset<int, greater <int>> sAlice, sBruno;
  for(auto card:alice)
      sAlice.insert(card);
    for(auto card:bruno)
        sBruno.insert(card);
    while(sAlice.size()!=0 && sBruno.size()!=0){
        auto iterA=sAlice.begin();
        auto iterB=sBruno.begin();
        if(*iterA>*iterB){
            int temp=*iterA-*iterB;
            sBruno.erase(iterB);
            sAlice.erase(iterA);
            sAlice.insert(temp);
        }
        else if(*iterA<*iterB){
            int temp=*iterB-*iterA;
            sBruno.erase(iterB);
            sAlice.erase(iterA);
            sBruno.insert(temp);

        }
        else{
            sBruno.erase(iterB);
            sAlice.erase(iterA);
        }
    }
    if(sAlice.size()>sBruno.size())
        return sAlice.size();
    else if(sAlice.size()<sBruno.size())
        return -sBruno.size();
    return 0;
}

// ----------------------------------------------------------
// Exercicio 3: Reviews Cinematograficas
// ----------------------------------------------------------

// ..............................
// a) Contando Filmes
// TODO
int FunWithBSTs::numberMovies(const vector<pair<string, int>>& reviews) {
  set<string > temp;
  for(auto review:reviews){
      temp.insert(review.first);
  }
  return temp.size();
}

// ..............................
// b) O filme com mais reviews
// TODO
void FunWithBSTs::moreReviews(const vector<pair<string, int>>& reviews, int& m, int& n) {
    map<string , int> temp;
    for(auto review:reviews){
        auto search =temp.find(review.first);
        if(search!=temp.end()){
            search->second++;
        }
        else{
            temp.insert(pair<string,int> (review.first, 1));
        }
    }
    m=0;
    for(auto movie: temp){
        if(movie.second>m)
            m=movie.second;
    }
    n=0;
    for(auto movie:temp){
        if(movie.second==m)
            n++;
    }
}

// ..............................
// c) Os melhores filmes
// TODO
vector<string> FunWithBSTs::topMovies(const vector<pair<string, int>>& reviews, double k) {
    vector<string> answer;
    map<string , double> nreview;
    map<string , double> media;
    for(auto review:reviews){
        auto search =nreview.find(review.first);
        auto search2 =media.find(review.first);
        if(search!=nreview.end()){
            search->second++;
        }
        if(search2!=media.end()){
            search->second+=review.second;
        }
        else{
            nreview.insert(pair<string,int> (review.first, 1));
            media.insert(pair<string,int> (review.first, review.second));
        }
    }
    auto it1=media.begin();
    for(auto movie:media){
        auto search =nreview.find(movie.first);
        movie.second=movie.second/search->second;
    }
    for(auto movie:media){
        if(movie.second>=k)
            answer.push_back(movie.first);
    }
    return answer;
}
