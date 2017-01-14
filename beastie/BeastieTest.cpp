/*!--------------------------------------------------------------------------*\
|   Binary Search Tree TDD exercise
\*---------------------------------------------------------------------------*/
#include "Beastie.hpp"

#include <gmock/gmock.h>
#include <algorithm>
#include <iostream>
#include <vector>

//! \fn     Fibo
//! \brief  Generates Fibonacci numbers for test data
int Fibo(int num)
{
    if (num < 2) {
        return num;
    }

    int fiboMinus1 = 1;
    int fiboMinus2 = 0;
    int fibo = 0;

    for (int i = 2; i <= num; ++i) {
        fibo = fiboMinus1 + fiboMinus2;
        fiboMinus2 = fiboMinus1;
        fiboMinus1 = fibo;
    }

    return fibo;
}

//! \class  BeastieTest
class BeastieTest: public ::testing::Test
{
public:
    virtual void SetUp()
    {
        for (int i = 0; i < 15; ++i) {
            fibos.push_back(Fibo(i));
        }

        std::random_shuffle(fibos.begin(), fibos.end());
    }

    Beastie<int> beastie;
    std::vector<int> fibos;

};

//! \test   EmptyTreeShouldReturnEmpty
TEST_F(BeastieTest, EmptyTreeShouldReturnEmpty) {
    EXPECT_TRUE(beastie.IsEmpty());
}

//! \test   TreeShouldNotBeEmptyAfterInsertion
TEST_F(BeastieTest, TreeShouldNotBeEmptyAfterInsertion) {
    beastie.Insert(55);
    EXPECT_FALSE(beastie.IsEmpty());
}

//! \test   TreeShouldNotBeEmptyAfterMultipleInsertions
TEST_F(BeastieTest, TreeShouldNotBeEmptyAfterMultipleInsertions) {
    for (auto value : fibos) {
        beastie.Insert(value);
    }

    EXPECT_FALSE(beastie.IsEmpty());
}

//! \fn     main
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}