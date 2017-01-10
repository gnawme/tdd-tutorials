#include "Slinky.hpp"

#include <gmock/gmock.h>
#include <string>

//! \class  SlinkyTest
class SlinkyTest: public ::testing::Test
{
public:
    virtual void SetUp()
    {
        slinky.Clear();
    }
    Slinky<std::string>     slinky;
    ListNode<std::string>*  current_node;
};

//! \test   EmptyListShouldReturnEmpty
TEST_F(SlinkyTest, EmptyListShouldReturnEmpty) {
    EXPECT_TRUE(slinky.IsEmpty());
}

//! \test   EmptyListShouldReturnSizeZero
TEST_F(SlinkyTest, EmptyListShouldReturnSizeZero) {
    EXPECT_EQ(slinky.Size(), 0);
}

//! \test   InsertionShouldReturnSizeOne
TEST_F(SlinkyTest, InsertionShouldReturnSizeOne) {
    current_node = slinky.Insert(new ListNode<std::string>("alpha"));
    EXPECT_EQ(slinky.Size(), 1);
}

//! \test   InsertionShouldReturnSameNode
TEST_F(SlinkyTest, InsertionShouldReturnSameNode) {
    current_node = slinky.Insert(new ListNode<std::string>("alpha"));
    ListNode<std::string>* new_node = new ListNode<std::string>("bravo");
    current_node = slinky.Insert(current_node, new_node);
    EXPECT_EQ(current_node, new_node);
}

//! \test   DeletionShouldDecrementCount
TEST_F(SlinkyTest, DeletionShouldDecrementCount) {
    ListNode<std::string>* last_node = new ListNode<std::string>("alpha");
    current_node = slinky.Insert(last_node);
    current_node = slinky.Insert(last_node, new ListNode<std::string>("bravo"));

    auto last_size = slinky.Size();
    current_node = slinky.Delete(last_node);
    EXPECT_LT(slinky.Size(), last_size);
}

//! \test   DeletionFromHeadShouldDecrementCount
TEST_F(SlinkyTest, DeletionFromHeadShouldDecrementCount) {
    current_node = slinky.Insert(new ListNode<std::string>("alpha"));
    current_node = slinky.Insert(current_node, new ListNode<std::string>("bravo"));

    auto last_size = slinky.Size();
    current_node = slinky.Delete();
    EXPECT_LT(slinky.Size(), last_size);
}

//! \test   ClearingListShouldReturnEmpty
TEST_F(SlinkyTest, ClearingListShouldReturnEmpty) {
    slinky.Clear();
    EXPECT_TRUE(slinky.IsEmpty());
}

//! \test   ListContentsShouldBeAlphaBravoCharlie
TEST_F(SlinkyTest, ListContentsShouldBeAlphaBravoCharlie) {
    current_node = slinky.Insert(new ListNode<std::string>("alpha"));
    current_node = slinky.Insert(current_node, new ListNode<std::string>("bravo"));
    current_node = slinky.Insert(current_node, new ListNode<std::string>("charlie"));

    std::vector<std::string> expected{"alpha", "bravo", "charlie"};
    std::vector<std::string> abc = slinky.PrintList();
    EXPECT_THAT(abc, ::testing::Eq(expected));
}

//! \test   ListContentsAfterReversalShouldBeCharlieBravoAlpha
TEST_F(SlinkyTest, ListContentsAfterReversalShouldBeCharlieBravoAlpha) {
    current_node = slinky.Insert(new ListNode<std::string>("alpha"));
    current_node = slinky.Insert(current_node, new ListNode<std::string>("bravo"));
    current_node = slinky.Insert(current_node, new ListNode<std::string>("charlie"));

    std::vector<std::string> expected{"charlie", "bravo", "alpha"};
    slinky.ReverseList();
    std::vector<std::string> cba = slinky.PrintList();
    EXPECT_THAT(cba, ::testing::Eq(expected));
}

//! \fn     main
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}