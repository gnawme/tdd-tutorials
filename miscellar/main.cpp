
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>

#include <gmock/gmock.h>

//! \fn     FiboIter
//! brief   Computes a Fibonacci number iteratively
int FiboIter(int num)
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

//! \fn     Fibo
//! \brief  Computes a Fibonacci number recursively
int Fibo(int num)
{
    if (num < 2) {
        return num;
    }

    return Fibo(num - 1) + Fibo(num - 2);
}

//! \fn     FindPalind
//! \brief  Determines if a string can be a palindrome
bool FindPalind(std::string &jumble)
{
    std::multimap<char, char> jumbleMap;
    std::set<char> jumbleSet;

    for (auto it : jumble) {
        jumbleMap.insert(std::pair<char, char>(it, it));
        jumbleSet.insert(it);
    }

    std::vector<char> mumble(jumbleSet.begin(), jumbleSet.end());

    int numOdds = 0;
    for (auto it : mumble) {
        auto numchars = jumbleMap.count(it);
        if (jumbleMap.count(it) % 2 != 0) {
            ++numOdds;
        }
    }

    return (numOdds <= 1);
}

//! \fn     Reversi
//! \brief  Reverses a character string in-place
char* Reversi(char* instr)
{
    auto len = strlen(instr);

    for (int i = 0, j = len - 1; i < len; ++i, --j) {
        char temp = instr[i];
        instr[i] = instr[j];
        instr[j] = temp;
    }

    return instr;
}

//! \test   CheckIfPalindromable
TEST(FindPalindTest, CheckIfPalindromable) {
    std::string testcase("aaabbbb");
    EXPECT_TRUE(FindPalind(testcase));
    testcase = "cdefghmnopqrstuvw";
    EXPECT_FALSE(FindPalind(testcase));
    testcase = "cdcdcdcdeeeef";
    EXPECT_TRUE(FindPalind(testcase));
}

//! \test   FiboRecursiveShouldEqualFiboIterative
TEST(FiboTest, FiboRecursiveShouldEqualFiboIterative) {
    for (int i = 1; i < 12; ++i) {
        std::cout << "Fibo[" << i << "] == " << Fibo(i) << " : " << FiboIter(i) << std::endl;
        EXPECT_EQ(Fibo(i), FiboIter(i));
    }
}

//! \test   ReversedStringShouldBeItsMirror
TEST(ReverseString, ReversedStringShouldBeItsMirror) {
    EXPECT_EQ(Reversi("a"), "a");
    EXPECT_EQ(Reversi("abcdefgh"), "hgfedcba");
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}