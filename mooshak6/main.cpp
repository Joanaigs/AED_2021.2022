#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int i,n, q;
    cin >>i;
    vector<int> s, p, sums;

    while(i>0){
        cin>>n;
        s.push_back(n);
        i--;
    }
    cin>>q;
    while(q>0){
        cin>>n;
        p.push_back(n);
        q--;
    }

    for(int i=0; i<s.size();i++) {
        for (int j = i+1; j < s.size(); j++) {
            sums.push_back(s[i]+s[j]);
        }
    }
    sort(sums.begin(), sums.end());
    for(auto el:p)
    {
        bool found=false;
        int left = 0, right = sums.size()-1;
        while (left<=right)
        {
            int mid =(left+right) / 2;
            if(sums[mid]<el)
                left=mid+1;
            else if(el<sums[mid])
                right=mid-1;
            else{
                cout<<sums[mid]<<endl;
                found=true;
                break;
            }
        }
        if(abs(sums[left]-el)>abs(sums[right]-el)&&!found)
            cout<<sums[right]<<endl;
        else if(abs(sums[left]-el)<abs(sums[right]-el)&&!found)
            cout<<sums[left]<<endl;
        else if (abs(sums[left]-el)==abs(sums[right]-el)&&!found)
            cout<<sums[right]<<" "<<sums[left]<<endl;
    }
    return 0;
}
