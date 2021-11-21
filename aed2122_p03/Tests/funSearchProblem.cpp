#include "funSearchProblem.h"

FunSearchProblem::FunSearchProblem() {}

//-----------------------------------------------------------------

// TODO
int FunSearchProblem::facingSun(const vector<int> & values) {
    if(values.size()==0)
        return 0;
    int n=1;
    int max=values[0];
    for(int i=1; i<values.size(); i++)
    {
        if(values[i]>max){
            max=values[i];
            n++;
        }
    }
    return n;
}

// TODO
int FunSearchProblem::squareR(int num) {
    int left=0, right=num/2;
    int middle;
    while(left<=right)
    {
        middle=(left+right)/2;
        if (middle*middle < num)
            left = middle + 1;
        else if(num<middle*middle)
            right =middle - 1;
        else
            return middle;
    }
    return middle;
}

// TODO
int FunSearchProblem::smallestMissingValue(const vector<int> & values) {
    int min;
    vector<int> minimos;
    bool positive=false;
    for(int i=0; i<values.size(); i++){
        if(values[i]>0) {
            positive = true;
        }
    }
    if(!positive)
        return 0;
    for(int i=1; i<values.size(); i++)
    {
        bool found=false;
        for(int j=0; j<values.size(); j++){
            if(values[j]==i){
                found= true;
            }
        }
        if(!found)
            minimos.push_back(i);
    }
    min=minimos[0];
    for(int i=0; i<minimos.size();i++){
        if(minimos[i]<min)
            min=minimos[i];
    }
    return min;
}

// TODO

int findkp(vector<int > &values, int atmost)
{
    int n = values.size();
    int s = 0, painters = 1;
    for (int i = 0; i < n; i++)
    {
        s += values[i];
        if (s > atmost)
        {
            s = values[i];
            painters++;
        }
    }
    return painters;
}

int FunSearchProblem::minPages(const vector<int> & values, int numSt) {
    int n = values.size(), s = 0, m = 0;
    for(int i = 0; i < n; i++)
    {
        m = max(m, values[i]);
        s += values[i];
    }
    int low = m, high = s;
    while (low < high)
    {
        int mid = low + (high-low) / 2;
        int painters = findkp(values, mid);
        if (painters <= numSt)
            high = mid;
        else low = mid + 1;
    }
    return low;
}

