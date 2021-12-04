#include <iostream>
#include <string>
#include <fstream>
#include "dictionary.h"

using namespace std;

WordMean::WordMean(string w, string m): word(w), meaning(m) {}

string WordMean::getWord() const {
    return word;
}

string WordMean::getMeaning() const {
    return meaning;
}

void WordMean::setMeaning(string m) {
    meaning = m;
}

void WordMean::setWord(string w) {
    word = w;
}

bool WordMean::operator<(const WordMean &word1) const {
    return (word<word1.word);
}

ostream &operator<<(ostream &out, const WordMean &word) {
    out<<word.getWord()<<endl<<word.getMeaning();
    return out;
}

BST<WordMean> Dictionary::getWords() const {
	return words;
}

// ---------------------------------------------

//TODO
void Dictionary::readFile(ifstream &f) {
    string name, meaning;
    while(getline(f, name)) {
        getline(f, meaning);
        words.insert(WordMean(name, meaning));
    }
}

//TODO
string Dictionary::consult(string word1, WordMean& previous, WordMean& next) const {

    WordMean temp(word1, "");
    auto t=words.find(temp);
    if(t.getWord()==""){
        for(auto iter= BSTItrIn<WordMean>(words); !iter.isAtEnd(); iter.advance()){
            if(word1<iter.retrieve().getWord()){
                next=iter.retrieve();
                break;
            }
            previous=iter.retrieve();
        }
        return string("word not found");
    }
    return t.getMeaning();
}

//TODO
bool Dictionary::update(string word1, string mean1) {
    WordMean temp(word1, "");
    auto t=words.find(temp);
    if(t.getWord()==""){
        words.insert(WordMean(word1, mean1));
        return false;
    }
    words.remove(t);
    t.setMeaning(mean1);
    words.insert(t);
    return true;
}

//TODO
void Dictionary::print() const {
    words.printTree();
}

