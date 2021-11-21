#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    int t, n, k;
    vector<int> values;
    cin>>t;
    for(int i=0; i<t; i++){
        cin>>n>>k;
        for(int j=n+1; ; j++)
        {
            int sum=0, temp=j;
            while(temp>0)
            {
                sum+=temp%10;
                temp/=10;
            }
            if(sum==k){
                values.push_back(j);
                break;
            }
        }
    }
    for(int val:values)
        cout<<val<<endl;
}
