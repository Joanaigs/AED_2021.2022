#include "funSortProblem.h"
#include <algorithm>

FunSortProblem::FunSortProblem() {}


//-----------------------------------------------------------------
bool comparePrice (Product i,Product j) {
    if (i.getPrice()<j.getPrice())
        return true;
    else if(i.getPrice()==j.getPrice())
        return (i.getWeight()<j.getWeight());
    else
        return false;
}

// TODO
//nlog(n)
void FunSortProblem::expressLane(vector<Product> &products, unsigned k) {
        sort(products.begin(),products.end(), comparePrice);
        if(k<=products.size())
            products.erase(products.begin()+k, products.end());
}
bool inverseSort (int i,int j) { return (i>j); }
// TODO
//nlog(n)
int FunSortProblem::minDifference(const vector<unsigned> &values, unsigned nc) {
    if(values.size()<nc)
        return -1;
    vector<unsigned> cop;
    copy(values.begin(),values.end(), back_inserter(cop));
    sort(cop.begin(),cop.end());
    int min=INT_MAX;
    for(int i=0; i<cop.size();i++)
    {
        if(i+nc-1<cop.size()){
            if(cop[i+nc-1]-cop[i]<min)
                min=cop[i+nc-1]-cop[i];
        }
    }
    return min;
}


// TODO
// N
unsigned FunSortProblem::minPlatforms (const vector<float> &arrival, const vector<float> &departure) {
    unsigned num=1;
    int add=1;
    for(int i=0; i<arrival.size(); i++){
        if(arrival[i+add]<departure[i]&&((i+add)<arrival.size())){
            add++;
            num++;
            i--;
        }
    }
    return num;
}


// TODO
template <class Comparable>
void
quickSort (vector<Comparable> &v, int left, int right ){
    if (right-left <= 10) // if small vector
    insertionSort(v , left, right);
    else {
        Comparable x = median3(v , left, right ); // x is the pivot
        int i = left; int j = right - 1;
        for(; ; ) {
            while (v[++i ] < x)
                while (x < v[j]) ;
            if (i < j)
                    swap(v[i ], v[j]);
            else break;
        }
        quickSort(v, left, i 1);
        quickSort(v, i+1, right)
    }
}
void FunSortProblem::nutsBolts(vector<Piece> &nuts, vector<Piece> &bolts) {

}

