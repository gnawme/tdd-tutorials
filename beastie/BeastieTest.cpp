/*!--------------------------------------------------------------------------*\
|   Binary search Tree TDD exercise
\*---------------------------------------------------------------------------*/
#include "Beastie.h"

#include <algorithm>
#include <gmock/gmock.h>
#include <iostream>
#include <random>

#include <vector>

///
/// \brief  Generates Fibonacci numbers for test data
int Fibo(int num) {
    if (num < 2) {
        return num;
    }

    int fiboMinus1{1};
    int fiboMinus2{0};
    int fibo{0};

    for (auto i = 2; i <= num; ++i) {
        fibo = fiboMinus1 + fiboMinus2;
        fiboMinus2 = fiboMinus1;
        fiboMinus1 = fibo;
    }

    return fibo;
}

/// \class  BeastieTest
class BeastieTest : public ::testing::Test {
public:
    void SetUp() override {
        constexpr int NUM_TEST_VALUES{15};
        for (auto i = 0; i < NUM_TEST_VALUES; ++i) {
            fibos.push_back(Fibo(i));
        }

        std::shuffle(fibos.begin(), fibos.end(), std::mt19937(std::random_device()()));
    }

    Beastie<int> beastie;
    std::vector<int> fibos;
    std::vector<int> simple{7, 1, 0, 3, 2, 5, 4, 6, 9, 8, 10};
};

/// \test   EmptyTreeShouldReturnEmpty
TEST_F(BeastieTest, EmptyTreeShouldReturnEmpty) {
    EXPECT_TRUE(beastie.isEmpty());
}

/// \test   TreeShouldNotBeEmptyAfterInsertion
TEST_F(BeastieTest, TreeShouldNotBeEmptyAfterInsertion) {
    beastie.insert(55);
    EXPECT_FALSE(beastie.isEmpty());
}

/// \test   TreeShouldNotBeEmptyAfterMultipleInsertions
TEST_F(BeastieTest, TreeShouldNotBeEmptyAfterMultipleInsertions) {
    for (auto key : fibos) {
        beastie.insert(key);
    }
    EXPECT_FALSE(beastie.isEmpty());
}

/// \test   SimpleInorderTraversalShouldYieldExpected
TEST_F(BeastieTest, SimpleInorderTraversalShouldYieldExpected) {
    for (auto key : simple) {
        beastie.insert(key);
    }

    beastie.traverseInorder(beastie.getRoot());

    std::vector<int> expected{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto compare{beastie.getTree()};
    EXPECT_THAT(compare, ::testing::ContainerEq(expected));
}

/// \test   SimplePreorderTraversalShouldYieldExpected
TEST_F(BeastieTest, SimplePreorderTraversalShouldYieldExpected) {
    for (auto key : simple) {
        beastie.insert(key);
    }

    beastie.traversePreorder(beastie.getRoot());

    std::vector<int> expected{7, 1, 0, 3, 2, 5, 4, 6, 9, 8, 10};
    auto compare{beastie.getTree()};
    EXPECT_THAT(compare, ::testing::ContainerEq(expected));
}

/// \test   SimplePostorderTraversalShouldYieldExpected
TEST_F(BeastieTest, SimplePostorderTraversalShouldYieldExpected) {
    for (auto key : simple) {
        beastie.insert(key);
    }

    beastie.traversePostorder(beastie.getRoot());

    std::vector<int> expected{0, 2, 4, 6, 5, 3, 1, 8, 10, 9, 7};
    auto compare{beastie.getTree()};
    EXPECT_THAT(compare, ::testing::ContainerEq(expected));
}

/// \test   TreeShouldBeEmptyAfterClear
TEST_F(BeastieTest, TreeShouldBeEmptyAfterClear) {
    for (auto key : simple) {
        beastie.insert(key);
    }

    beastie.clear();
    EXPECT_TRUE(beastie.isEmpty());
}

/// \test   SearchForValueInTreeShouldReturnNode
TEST_F(BeastieTest, SearchForValueInTreeShouldReturnNode) {
    for (auto key : fibos) {
        beastie.insert(key);
    }

    auto node{beastie.search(55)};
    ASSERT_TRUE(node != nullptr);
}

/// \test   SearchForValueNotInTreeShouldReturnNull
TEST_F(BeastieTest, SearchForValueNotInTreeShouldReturnNull) {
    for (auto key : fibos) {
        beastie.insert(key);
    }

    auto node{beastie.search(42)};
    ASSERT_TRUE(node == nullptr);
}

/// \test   DepthOfTreeShouldBeGreaterThanOne
TEST_F(BeastieTest, DepthOfTreeShouldBeGreaterThanOne) {
    for (auto key : simple) {
        beastie.insert(key);
    }

    int depth{beastie.depth()};

    ASSERT_TRUE(depth > 0);
}

/// \test   InorderTraversalShouldBeSameAsSorted
TEST_F(BeastieTest, InorderTraversalShouldBeSameAsSorted) {
    beastie.traverseInorder(beastie.getRoot());
    std::vector<int> compare = beastie.getTree();
    std::vector<int> sorted{compare.begin(), compare.end()};
    std::sort(sorted.begin(), sorted.end());

    EXPECT_THAT(compare, ::testing::ContainerEq(sorted));
}

/// \test   NumberOfPathsInEmptyListShouldBeZero
TEST_F(BeastieTest, NumberOfPathsInEmptyListShouldBeZero) {
    EXPECT_EQ(0, beastie.numPaths());
}

/// \test   NumberOfPathsInSimpleTreeShouldBeGreaterThanZero
TEST_F(BeastieTest, NumberOfPathsInSimpleTreeShouldBeGreaterThanZero) {
    for (auto key : simple) {
        beastie.insert(key);
    }

    beastie.findPaths();
    EXPECT_TRUE(beastie.numPaths() > 0);
}

/// \test   CopyConstructorShouldReturnIdenticalTree
TEST_F(BeastieTest, CopyConstructorShouldReturnIdenticalTree) {
    for (auto key : simple) {
        beastie.insert(key);
    }

    beastie.traversePreorder(beastie.getRoot());
    std::vector<int> compare = beastie.getTree();

    Beastie<int> bestie(beastie);
    bestie.traversePreorder(bestie.getRoot());

    EXPECT_THAT(compare, ::testing::ContainerEq(bestie.getTree()));
}

/// \test   AssignmentOperatorShouldReturnIdenticalTree
TEST_F(BeastieTest, AssignmentOperatorShouldReturnIdenticalTree) {
    for (auto key : fibos) {
        beastie.insert(key);
    }

    beastie.traversePreorder(beastie.getRoot());
    auto compare{beastie.getTree()};

    auto bestie{beastie};
    bestie.traversePreorder(bestie.getRoot());

    EXPECT_THAT(compare, ::testing::ContainerEq(bestie.getTree()));
}

/// \test   MoveConstructorShouldReturnIdenticalTree
TEST_F(BeastieTest, MoveConstructorShouldReturnIdenticalTree) {
    for (auto key : fibos) {
        beastie.insert(key);
    }

    beastie.traversePreorder(beastie.getRoot());
    auto compare{beastie.getTree()};

    auto bestie(std::move(beastie));
    bestie.traversePreorder(bestie.getRoot());

    EXPECT_THAT(compare, ::testing::ContainerEq(bestie.getTree()));
}

/// \test   MoveAssignmentOperatorShouldReturnIdenticalTree
TEST_F(BeastieTest, MoveAssignmentOperatorShouldReturnIdenticalTree) {
    for (auto key : fibos) {
        beastie.insert(key);
    }

    beastie.traversePreorder(beastie.getRoot());
    auto compare{beastie.getTree()};

    Beastie<int> bestie = std::move(beastie);
    bestie.traversePreorder(bestie.getRoot());

    EXPECT_THAT(compare, ::testing::ContainerEq(bestie.getTree()));
}

///
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}