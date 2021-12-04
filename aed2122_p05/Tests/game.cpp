#include "game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
using namespace std;


unsigned int Game::numberOfWords(string phrase) {
  if ( phrase.length() == 0 ) return 0;

  unsigned n=1;
  size_t pos = phrase.find(' ');
  while (pos != string::npos) {
    phrase = phrase.substr(pos+1);
    pos = phrase.find(' ');
    n++;
  }
  return n;
}

Game::Game() {
	this->kids.clear();
}

Game::Game(list<Kid>& l2) {
	this->kids = l2;
}

//-----------------------------------------------------------------

// TODO
void Game::addKid(const Kid k1) {
    kids.push_back(k1);
}

// TODO
list<Kid> Game::getKids() const {
    return (kids);
}

// TODO
void Game::setKids(const list<Kid>& l1) {
    kids=l1;
}

// TODO
Kid Game::loseGame(string phrase) {
    unsigned n = numberOfWords(phrase);
    list<Kid>::iterator it = kids.begin();
    while(kids.size()>1) {
        int nsteps=(n-1)%kids.size();
        for (int i = 1; i <= nsteps; i++) {
            it++;
            if (it == kids.end())
                it = kids.begin();
        }
        it=kids.erase(it);
        if (it == kids.end())
            it = kids.begin();
    }
    return *it;
}

// TODO
list<Kid> Game::removeOlder(unsigned id) {
    return (list<Kid>());
}

// TODO
queue<Kid> Game::rearrange() {
    list<Kid> tempKid;
    queue<Kid> girls, boys, result;
    list<Kid>::iterator it=kids.begin();
    for(it; it!=kids.end(); it++){
        if(it->getSex()=='f')
            girls.push(*it);
        if(it->getSex()=='m')
            boys.push(*it);
    }
    int n=girls.size(), m=boys.size();
    if(n<m){
        int temp=m/n;
        while(n>=1 && m>=temp)
        {
            tempKid.push_back(girls.front());
            girls.pop();
            for(int j=0; j<temp; j++){
                tempKid.push_back(boys.front());
                boys.pop();
            }
            n=girls.size();
            m=boys.size();
        }

    }
    else{
        int temp=n/m;
        while(m>=1&&n>=temp)
        {
            for(int j=0; j<temp; j++){
                tempKid.push_back(girls.front());
                girls.pop();
            }
            tempKid.push_back(boys.front());
            boys.pop();
            n=girls.size();
            m=boys.size();
        }
    }
    for(int i=0;i<boys.size();i++){
        result.push(boys.front());
        boys.pop();
    }
    for(int i=0;i<girls.size();i++){
        result.push(girls.front());
        girls.pop();
    }
    kids=tempKid;
    return result;
}

// TODO
bool Game::operator==(Game& g2) {
	bool equal = true;
    if(kids.size()!=g2.getKids().size())
        return false;
    list<Kid> kids1=g2.getKids();
    list<Kid>::iterator it1=kids.begin(), it2=kids1.begin();
    for(int i=0; i<kids.size();i++){
        if(*it1==*it2){
        }
        else{
            equal=false;
            break;
        }
        it1++;
        it2++;
    }
    return equal;
}

// TODO
list<Kid> Game::shuffle() const {
    srand (time(NULL));
    auto it=kids.begin();
    list<Kid> kidsrand=kids;
    auto it1=kidsrand.begin();
    for(int i=0; i<kids.size();i++){
        int n=rand()%kids.size();
        advance(it1, n);
        *it1=*it;
        it1=kidsrand.begin();
        it++;
    }
    return kidsrand;
}
