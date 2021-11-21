#ifndef SRC_FUNSP_H_
#define SRC_FUNSP_H_

#include <iostream>
#include <vector>

using namespace std;

class FunSearchProblem{
public:
    /**
     *Constructor
     */
    FunSearchProblem();
    static int smallestMissingValue(const vector<int> & values);
    /**
     *
     * @param values vector with the heights of different skyscrapers
     * @return returns the number of buildings that can see the sun
     */
    static int facingSun(const vector<int> & values);
    /**
     *
     * @param num number which we want to find tge square root
     * @return the square root of the number
     */
    static int squareR(int num);
    static int findkp(cont vector<int > &values, int atmost);
    static int minPages(const vector<int> & values, int numSt);
};

#endif