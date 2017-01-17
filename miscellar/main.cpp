
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>

#include <gmock/gmock.h>

//! \fn     AckermannFn
//! \brief  Computes Ackermann's function recursively
int AckermannFn(int m, int n)
{
    if (m == 0) {
        return n + 1;
    }

    if (n == 0) {
        return AckermannFn(m - 1, 1);
    }

    return AckermannFn(m - 1, AckermannFn(m, n - 1));
}

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
        EXPECT_EQ(Fibo(i), FiboIter(i));
    }
}

//! \test   ReversedStringShouldBeItsMirror
TEST(ReverseString, ReversedStringShouldBeItsMirror) {
    char alpha8[] = "abcdefgh";
    char* ahpla8 = Reversi(alpha8);
    EXPECT_TRUE(strcmp(alpha8, ahpla8) == 0);
}

//! \test   TestRecursiveAckermannFunction
TEST(Ackermann, TestRecursiveAckermannFunction) {
    EXPECT_EQ(AckermannFn(0, 1), 2);
    EXPECT_EQ(AckermannFn(1, 0), AckermannFn(0, 1));
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}