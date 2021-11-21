#include <iostream>


int main() {
    int n, s, total=0;
    std::cin>>n;
    for(int i=0; i<n; i++)
    {
        std::cin>>s;
        if(s==42)
            total+=1;

    }
    std::cout<<total<<std::endl;
}
