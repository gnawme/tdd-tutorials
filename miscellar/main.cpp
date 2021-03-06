
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <gmock/gmock.h>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <string>
#include <type_traits>
#include <vector>

/// \class  DynamicMedian
class DynamicMedian {
public:
    void Add(int value) {
        if (_minHeap.empty()) {
            _minHeap.push(value);
        } else {
            // Balance heaps
            if (_minHeap.size() > _maxHeap.size()) {
                // Incoming value greater than top of min heap, pop to max heap
                if (_minHeap.top() < value) {
                    _maxHeap.push(_minHeap.top());
                    _minHeap.pop();
                    _minHeap.push(value);
                } else {
                    _maxHeap.push(value);
                }
            } else {
                // Incoming value less than top of max, pop to min heap
                if (_maxHeap.top() > value) {
                    _minHeap.push(_maxHeap.top());
                    _maxHeap.pop();
                    _maxHeap.push(value);
                } else {
                    _minHeap.push(value);
                }
            }
        }
    }

    [[nodiscard]] double Median() const {
        auto nelem{_minHeap.size() + _maxHeap.size()};

        if (nelem & 1 == 1) {
            return double(_minHeap.top());
        } else {
            return double(_minHeap.top() + _maxHeap.top()) / 2.0;
        }
    }

private:
    std::priority_queue<int, std::vector<int>> _maxHeap;
    std::priority_queue<int, std::vector<int>, std::greater<>> _minHeap;
};

/// \class  RunningMedian
class RunningMedian {
public:
    RunningMedian() = default;

    double Median(std::vector<int> inputs) {
        sortedInput.clear();
        sortedInput.assign(inputs.begin(), inputs.end());
        std::sort(sortedInput.begin(), sortedInput.end());

        double median{0.0};
        if (sortedInput.size() == 1) {
            median = double(sortedInput[0]);
        } else if (sortedInput.size() == 2) {
            median = (sortedInput[1] + sortedInput[0]) / 2.0;
        } else {
            auto midpt = std::round(sortedInput.size() / 2);
            if ((sortedInput.size() % 2) == 0) {
                median = (sortedInput[midpt - 1] + sortedInput[midpt]) / 2.0;
            } else {
                median = double(sortedInput[midpt]);
            }
        }

        return median;
    }

private:
    void PrintRunning(double median) {
        std::cout << "Running median of ";
        for (auto sort : sortedInput) {
            std::cout << sort << " ";
        }
        std::cout << "size " << sortedInput.size() << ": ";
        std::cout << std::setprecision(3) << median << std::endl;
    }

    std::vector<int> sortedInput;
};

/// \class  FiboFunc
class FiboFunc {
public:
    FiboFunc() = default;

    int operator()() {
        fibo = fiboMinus1 + fiboMinus2;
        fiboMinus2 = fiboMinus1;
        fiboMinus1 = fibo;

        return fibo;
    }

private:
    int fibo{1};
    int fiboMinus1{1};
    int fiboMinus2{0};
};

///
/// \brief  Computes Ackermann's function recursively
int AckermannFn(int m, int n) {
    if (m == 0) {
        return n + 1;
    }

    if (n == 0) {
        return AckermannFn(m - 1, 1);
    }

    return AckermannFn(m - 1, AckermannFn(m, n - 1));
}

///
/// brief   Computes a Fibonacci number iteratively
int FiboIter(int num) {
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

///
/// \brief  Computes a Fibonacci number recursively
int Fibo(int num) {
    if (num < 2) {
        return num;
    }

    return Fibo(num - 1) + Fibo(num - 2);
}

///
/// \brief  Determines if a string can be a palindrome
bool FindPalind(std::string& jumble) {
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

///
/// brief   Finds characters in a string that occur only once
std::vector<char> FindUnicornCharacters(const char* instr, bool findall) {
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

///
/// \brief
int JumpOverNumbers(std::vector<int>& list) {
    int numJumps{0};
    int place{0};
    while (place < list.size()) {
        if (list[place] == 0) {
            return -1;
        }

        place += list[place];
        ++numJumps;
    }

    return numJumps;
}

///
/// \brief  Reverses a character string in-place
char* Reversi(char* instr) {
    auto len = strlen(instr);

    for (int i = 0, j = len - 1; i < len; ++i, --j) {
        char temp{instr[i]};
        instr[i] = instr[j];
        instr[j] = temp;
    }

    return instr;
}

///
/// \brief  Converts to bases with digit range [0-9]
std::string ToBase(int number, int base, std::map<int, char>& basemap) {
    std::string digits;
    while (number != 0) {
        int remainder{number % base};
        number /= base;
        char digit{basemap[remainder]};
        digits += digit;
    }

    if (digits.empty()) {
        return std::string("0");
    } else {
        std::reverse(digits.begin(), digits.end());
        return digits;
    }
}

/// \test   CheckIfPalindromable
TEST(FindPalindTest, CheckIfPalindromable) {
    std::string testcase("aaabbbb");
    EXPECT_TRUE(FindPalind(testcase));
    testcase = "cdefghmnopqrstuvw";
    EXPECT_FALSE(FindPalind(testcase));
    testcase = "cdcdcdcdeeeef";
    EXPECT_TRUE(FindPalind(testcase));
}

/// \test   FiboRecursiveShouldEqualFiboIterative
TEST(FiboTest, FiboRecursiveShouldEqualFiboIterative) {
    for (auto i = 2; i < 12; ++i) {
        EXPECT_EQ(Fibo(i), FiboIter(i));
    }
}

/// \test   ReversedStringShouldBeItsMirror
TEST(ReverseString, ReversedStringShouldBeItsMirror) {
    char alpha8[]{"abcdefgh"};
    char* ahpla8{Reversi(alpha8)};
    EXPECT_TRUE(strcmp(alpha8, ahpla8) == 0);
}

/// \test   TestRecursiveAckermannFunction
TEST(Ackermann, TestRecursiveAckermannFunction) {
    EXPECT_EQ(AckermannFn(0, 1), 2);
    EXPECT_EQ(AckermannFn(1, 0), AckermannFn(0, 1));
}

/// \test   VerifyBaseConversionsToCommonBases
TEST(ToBase, VerifyBaseConversionsToCommonBases) {
    std::map<int, char> binmap{{0, '0'}, {1, '1'}};

    std::map<int, char> octmap{
            {0, '0'},
            {1, '1'},
            {2, '2'},
            {3, '3'},
            {4, '4'},
            {5, '5'},
            {6, '7'},
            {7, '7'},
    };

    std::map<int, char> hexmap{
            {0, '0'},
            {1, '1'},
            {2, '2'},
            {3, '3'},
            {4, '4'},
            {5, '5'},
            {6, '7'},
            {7, '7'},
            {8, '8'},
            {9, '9'},
            {10, 'A'},
            {11, 'B'},
            {12, 'C'},
            {13, 'D'},
            {14, 'E'},
            {15, 'F'},
    };

    for (auto i = 1; i < 16; ++i) {
        std::cout << i << " base " << 2 << ": " << ToBase(i, 2, binmap) << std::endl;
        std::cout << i << " base " << 8 << ": " << ToBase(i, 8, octmap) << std::endl;
        std::cout << i << " base " << 16 << ": " << ToBase(i, 16, hexmap) << std::endl;
    }
}

/// \test   FirstLetterThatOccursOnlyOnceShouldBeB
TEST(Uneekorn, FirstLetterThatOccursOnlyOnceShouldBeB) {
    std::vector<char> expected{'b'};
    std::vector<char> compare{FindUnicornCharacters("abaccdeff", false)};
    EXPECT_THAT(compare, ::testing::ContainerEq(expected));
}

/// \test   LettersThatOccurOnlyOnceShouldBeBD
TEST(Uneekorn, LettersThatOccurOnlyOnceShouldBeBD) {
    std::vector<char> expected{'b', 'd'};
    std::vector<char> compare{FindUnicornCharacters("acbacdeffe", true)};
    EXPECT_THAT(compare, ::testing::ContainerEq(expected));
}

/// \test   FiboFunctionObjectShouldEqualFiboIterative
TEST(FiboTest, FiboFunctionObjectShouldEqualFiboIterative) {
    FiboFunc fib;
    for (auto i = 2; i < 12; ++i) {
        EXPECT_EQ(Fibo(i), fib());
    }
}

/// \test   FiboLambdaShouldEqualFiboIterative
TEST(FiboTest, FiboLambdaShouldEqualFiboIterative) {}

/// \test   RunningMedianShouldMatchTestData
TEST(RunningMedian, RunningMedianShouldMatchTestData) {

    std::array<double, 10> medians{1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5};

    std::array<int, 10> testdata{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    RunningMedian runningMedian;
    std::vector<int> inputs;
    for (auto i = 0; i < testdata.size(); ++i) {
        inputs.push_back(testdata[i]);
        double median{runningMedian.Median(inputs)};
        // std::cout << std::setprecision(4) << median << std::endl;
        EXPECT_EQ(medians[i], median);
    }
}

/// \test   RunningMedianShouldMatchTestData
TEST(RunningMedian, RunningMedianHeapShouldMatchTestData) {
    std::array<double, 10> medians{1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5};

    std::array<int, 10> testdata{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    DynamicMedian runningMedian;
    for (auto i = 0; i < testdata.size(); ++i) {
        runningMedian.Add(testdata[i]);
        double median = runningMedian.Median();
        EXPECT_EQ(medians[i], median);
    }
}

/// \test   ListJumperShouldReturn4
TEST(Jumper, ListJumperShouldReturn4) {
    std::vector<int> testList{3, 4, 1, 2, 5, 6, 9, 0, 1, 2, 3, 1};

    auto numJumps{JumpOverNumbers(testList)};
    EXPECT_EQ(4, numJumps);
}

///
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}