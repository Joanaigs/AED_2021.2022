#include <iostream>
#include <list>
using namespace std;

struct Frequencia{
    char alph =' ';
    int n=0;
    Frequencia(char i, int i1) {
        alph=i; n=i1;
    }
};

bool compare(const Frequencia& first, const Frequencia& second){
    return (first.n>second.n);
}

int main() {

    list<Frequencia> adn;
    string in;
    cin>>in;

    for(int i=0; i<in.length();i++){
        list<Frequencia>::iterator it;
        bool found=false;
        for ( it=adn.begin(); it != adn.end(); it++){
            if(it->alph == in[i]) {
                it->n = it->n + 1;
                found=true;
                break;
            }
        }
        if(!found) {
            Frequencia temp(in[i], 1);
            adn.push_back(temp);
        }
    }
    adn.sort(compare);
    for(Frequencia temp:adn){
        cout<<temp.alph<<" "<<temp.n<<endl;
    }

    return 0;
}
