#include <iostream>
#include <vector>

using namespace std;

template <class T>
class MyVector {
    vector<T> values;
public:
    MyVector();
    ~MyVector();
    void push_back(T v1);
    vector<T> getValues() const;
    T max() const;
    bool hasDuplicates() const;
    void removeDuplicates() ;
    void fillVector(int size);
};


// exception EmptyVector
class EmptyVector
{ };

// methods
template <class T>
MyVector<T>::MyVector() {}

template <class T>
MyVector<T>::~MyVector() {}

template <class T>
void MyVector<T>::push_back(T v1) {
    values.push_back(v1);
}

template <class T>
vector<T> MyVector<T>::getValues() const {
    return values;
}

//---------------------------------

// TODO
template <class T>
T MyVector<T>::max() const {
    if (values.size()==0)
        throw(EmptyVector());
    T vmax=values[0];
    for(int i=1;i<values.size(); i++)
        if(values[i]>vmax)
            vmax=values[i];
	return vmax;
}

// TODO
template<class T>
bool MyVector<T>::hasDuplicates() const {
    for(int i=0;i<values.size(); i++)
    {
        for(int j=i+1; j<values.size(); j++)
        {
            if(values[i]==values[j])
                return true;
        }
    }
	return false;
}

// TODO
template<class T>
void MyVector<T>::removeDuplicates() {
    for(int i=0;i<values.size(); i++)
    {
        for(int j=i+1; j<values.size(); j++)
        {
            if(values[i]==values[j])
            {
                values.erase(values.begin()+j);
                j--;
            }
        }
    }
}

template<class T>
void MyVector<T>::fillVector(int size) {
    for(int i=0; i<size; i++)
        values.push_back(i);
}

