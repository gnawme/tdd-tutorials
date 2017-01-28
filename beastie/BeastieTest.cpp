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
    std::vector<int> simple{7, 1, 0, 3, 2, 5, 4, 6, 9, 8, 10};

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
    for (auto key : fibos) {
        beastie.Insert(key);
    }
    EXPECT_FALSE(beastie.IsEmpty());
}

//! \test   SimpleInorderTraversalShouldYieldExpected
TEST_F(BeastieTest, SimpleInorderTraversalShouldYieldExpected) {
    for (auto key : simple) {
        beastie.Insert(key);
    }

    beastie.TraverseInorder(beastie.GetRoot());

    std::vector<int> expected{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> compare = beastie.GetTree();
    EXPECT_THAT(compare, ::testing::ContainerEq(expected));
}

//! \test   SimplePreorderTraversalShouldYieldExpected
TEST_F(BeastieTest, SimplePreorderTraversalShouldYieldExpected) {
    for (auto key : simple) {
        beastie.Insert(key);
    }

    beastie.TraversePreorder(beastie.GetRoot());

    std::vector<int> expected{7, 1, 0, 3, 2, 5, 4, 6, 9, 8, 10};
    std::vector<int> compare = beastie.GetTree();
    EXPECT_THAT(compare, ::testing::ContainerEq(expected));
}

//! \test   SimplePostorderTraversalShouldYieldExpected
TEST_F(BeastieTest, SimplePostorderTraversalShouldYieldExpected) {
    for (auto key : simple) {
        beastie.Insert(key);
    }

    beastie.TraversePostorder(beastie.GetRoot());

    std::vector<int> expected{0, 2, 4, 6, 5, 3, 1, 8, 10, 9, 7};
    std::vector<int> compare = beastie.GetTree();
    EXPECT_THAT(compare, ::testing::ContainerEq(expected));
}

//! \test   TreeShouldBeEmptyAfterClear
TEST_F(BeastieTest, TreeShouldBeEmptyAfterClear) {
    for (auto key : simple) {
        beastie.Insert(key);
    }

    beastie.Clear();
    EXPECT_TRUE(beastie.IsEmpty());
}

//! \test   SearchForValueInTreeShouldReturnNode
TEST_F(BeastieTest, SearchForValueInTreeShouldReturnNode) {
    for (auto key : fibos) {
        beastie.Insert(key);
    }

    BSTNode<int>* node = beastie.Search(55);
    ASSERT_TRUE(node != nullptr);
}

//! \test   SearchForValueNotInTreeShouldReturnNull
TEST_F(BeastieTest, SearchForValueNotInTreeShouldReturnNull) {
    for (auto key : fibos) {
        beastie.Insert(key);
    }

    BSTNode<int>* node = beastie.Search(42);
    ASSERT_TRUE(node == nullptr);
}

//! \test   DepthOfTreeShouldBeGreaterThanOne
TEST_F(BeastieTest, DepthOfTreeShouldBeGreaterThanOne) {
    for (auto key : simple) {
        beastie.Insert(key);
    }

    int depth = beastie.Depth();

    ASSERT_TRUE(depth > 0);
}

//! \test   InorderTraversalShouldBeSameAsSorted
TEST_F(BeastieTest, InorderTraversalShouldBeSameAsSorted) {
    beastie.TraverseInorder(beastie.GetRoot());
    std::vector<int> compare = beastie.GetTree();
    std::vector<int> sorted{compare.begin(), compare.end()};
    std::sort(sorted.begin(), sorted.end());

    EXPECT_THAT(compare, ::testing::ContainerEq(sorted));
}

//! \test   NumberOfPathsInEmptyListShouldBeZero
TEST_F(BeastieTest, NumberOfPathsInEmptyListShouldBeZero) {
    EXPECT_EQ(0, beastie.NumPaths());
}

//! \test   NumberOfPathsInSimpleTreeShouldBeGreaterThanZero
TEST_F(BeastieTest, NumberOfPathsInSimpleTreeShouldBeGreaterThanZero) {
    for (auto key : simple) {
        beastie.Insert(key);
    }

    beastie.FindPaths();
    EXPECT_TRUE(beastie.NumPaths() > 0);
}

//! \test   CopyConstructorShouldReturnIdenticalTree
TEST_F(BeastieTest, CopyConstructorShouldReturnIdenticalTree) {
    for (auto key : simple) {
        beastie.Insert(key);
    }

    beastie.TraversePreorder(beastie.GetRoot());
    std::vector<int> compare = beastie.GetTree();

    Beastie<int> bestie(beastie);
    bestie.TraversePreorder(bestie.GetRoot());

    EXPECT_THAT(compare, ::testing::ContainerEq(bestie.GetTree()));
}

//! \test   AssignmentOperatorShouldReturnIdenticalTree
TEST_F(BeastieTest, AssignmentOperatorShouldReturnIdenticalTree) {
    for (auto key : fibos) {
        beastie.Insert(key);
    }

    beastie.TraversePreorder(beastie.GetRoot());
    std::vector<int> compare = beastie.GetTree();

    Beastie<int> bestie = beastie;
    bestie.TraversePreorder(bestie.GetRoot());

    EXPECT_THAT(compare, ::testing::ContainerEq(bestie.GetTree()));
}

//! \test   MoveConstructorShouldReturnIdenticalTree
TEST_F(BeastieTest, MoveConstructorShouldReturnIdenticalTree) {
    for (auto key : fibos) {
        beastie.Insert(key);
    }

    beastie.TraversePreorder(beastie.GetRoot());
    std::vector<int> compare = beastie.GetTree();

    Beastie<int> bestie(std::move(beastie));
    bestie.TraversePreorder(bestie.GetRoot());

    EXPECT_THAT(compare, ::testing::ContainerEq(bestie.GetTree()));
}

//! \test   MoveAssignmentOperatorShouldReturnIdenticalTree
TEST_F(BeastieTest, MoveAssignmentOperatorShouldReturnIdenticalTree) {
    for (auto key : fibos) {
        beastie.Insert(key);
    }

    beastie.TraversePreorder(beastie.GetRoot());
    std::vector<int> compare = beastie.GetTree();

    Beastie<int> bestie = std::move(beastie);
    bestie.TraversePreorder(bestie.GetRoot());

    EXPECT_THAT(compare, ::testing::ContainerEq(bestie.GetTree()));

}

//! \fn     main
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}