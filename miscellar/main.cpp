
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>

#include <gmock/gmock.h>
#include <memory>
#include <set>

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

//! \fn     FindUnicornCharacters
//! brief   Finds characters in a string that occur only once
std::vector<char> FindUnicornCharacters(const char* instr, bool findall)
{
    if (instr == nullptr) {
        return std::vector<char>();
    }

    std::string instring(instr);
    std::multiset<char> charmap;

    for (auto achar : instring) {
        charmap.insert(achar);
    }

    bool first = true;
    std::vector<char> unicorns;
    for (auto inmap : charmap) {
        if (charmap.count(inmap) == 1) {
            unicorns.push_back(inmap);

            if (!findall && first) {
                return unicorns;
            }

            first = false;
        }
    }

    return unicorns;
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

//! \fn     ToBase
//! \brief  Converts to bases with digit range [0-9]
std::string ToBase(int number, int base, std::map<int, char>& basemap)
{
    std::string digits;
    while (number != 0) {
        int remainder = number % base;
        number /= base;
        char digit = basemap[remainder];
        digits += digit;
    }

    if (digits.empty()) {
        return std::string("0");
    } else {
        std::reverse(digits.begin(), digits.end());
        return digits;
    }
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

//! \test   VerifyBaseConversionsToCommonBases
TEST(ToBase, VerifyBaseConversionsToCommonBases) {
    std::map<int, char> binmap{
        {0, '0'}, {1, '1'}
    };

    std::map<int, char> octmap{
        {0, '0'}, {1, '1'}, {2, '2'}, {3, '3'},
        {4, '4'}, {5, '5'}, {6, '7'}, {7, '7'},
    };

    std::map<int, char> hexmap{
        {0, '0'}, {1, '1'}, {2, '2'}, {3, '3'},
        {4, '4'}, {5, '5'}, {6, '7'}, {7, '7'},
        {8, '8'}, {9, '9'}, {10, 'A'}, {11, 'B'},
        {12, 'C'}, {13, 'D'}, {14, 'E'}, {15, 'F'},
    };

    for (auto i = 1; i < 16; ++i) {
        std::cout << i << " base " << 2 << ": " << ToBase(i, 2, binmap) << std::endl;
        std::cout << i << " base " << 8 << ": " << ToBase(i, 8, octmap) << std::endl;
        std::cout << i << " base " << 16 << ": " << ToBase(i, 16, hexmap) << std::endl;
    }
}

//! \test   FirstLetterThatOccursOnlyOnceShouldBeB
TEST(Uneekorn, FirstLetterThatOccursOnlyOnceShouldBeB) {
    std::vector<char> expected{'b'};
    std::vector<char> compare = FindUnicornCharacters("abaccdeff", false);
    EXPECT_THAT(compare, ::testing::ContainerEq(expected));

}

//! \test   LettersThatOccurOnlyOnceShouldBeBD
TEST(Uneekorn, LettersThatOccurOnlyOnceShouldBeBD) {
    std::vector<char> expected{'b', 'd'};
    std::vector<char> compare = FindUnicornCharacters("acbacdeffe", true);
    EXPECT_THAT(compare, ::testing::ContainerEq(expected));

}


//! \fn     main
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}