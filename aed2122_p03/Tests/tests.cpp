#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "funSearchProblem.h"

using testing::Eq;

TEST(test, facingsun){
    vector<int> v0={};
    vector<int> v1 ={10, 7, 20, 15, 38};
    vector<int> v2={3, 10, 10, 2,1};
    vector<int> v3={10, 8, 7, 5};
    vector<int> v4={2, 3, 8};
    FunSearchProblem funny;
    EXPECT_EQ(3,funny.facingSun(v1));
    EXPECT_EQ(0,funny.facingSun(v0));
    EXPECT_EQ(2,funny.facingSun(v2));
    EXPECT_EQ(1,funny.facingSun(v3));
    EXPECT_EQ(3,funny.facingSun(v4));
}

TEST(test, squareR){
    FunSearchProblem funny;
    EXPECT_EQ(2, funny.squareR(4));
    EXPECT_EQ(2, funny.squareR(5));
}

TEST(test, missingvalue){

    FunSearchProblem funny;
    vector<int> v1 ={-1, -2, -10, 0, 0};
    EXPECT_EQ(0, funny.smallestMissingValue(v1));

}

TEST(test, minPages){
    FunSearchProblem funny;
    vector<int> v1 ={10, 20, 30, 40};
}
