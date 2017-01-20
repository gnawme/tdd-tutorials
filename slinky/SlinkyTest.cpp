#include "Slinky.hpp"

#include <gmock/gmock.h>
#include <array>
#include <string>

//! \class  SlinkyTest
class SlinkyTest: public ::testing::Test
{
public:
    virtual void SetUp()
    {
        slinky.Clear();
    }

    void InsertNATO(int count)
    {
        current_node = slinky.Insert(new ListNode<std::string>(natos[0]));
        for (auto i = 1; i < count; ++i) {
            current_node = slinky.Insert(current_node, new ListNode<std::string>(natos[i]));
        }
    }

    std::array<std::string, 26> natos{
        {
            "alfa", "bravo", "charlie", "delta", "echo", "foxtrot",
            "golf", "hotel", "india", "juliett", "kilo", "lima",
            "mike", "november", "oscar", "papa", "quebec", "romeo",
            "sierra", "tango", "uniform", "victor", "whiskey", "x-ray",
            "yankee", "zulu"
        }
    };

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
    current_node = slinky.Insert(new ListNode<std::string>(natos[0]));
    EXPECT_EQ(slinky.Size(), 1);
}

//! \test   InsertionShouldReturnSameNode
TEST_F(SlinkyTest, InsertionShouldReturnSameNode) {
    current_node = slinky.Insert(new ListNode<std::string>(natos[0]));
    ListNode<std::string>* new_node = new ListNode<std::string>(natos[1]);
    current_node = slinky.Insert(current_node, new_node);
    EXPECT_EQ(current_node, new_node);
}

//! \test   DeletionShouldDecrementCount
TEST_F(SlinkyTest, DeletionShouldDecrementCount) {
    ListNode<std::string>* last_node = new ListNode<std::string>(natos[0]);
    current_node = slinky.Insert(last_node);
    current_node = slinky.Insert(last_node, new ListNode<std::string>(natos[1]));

    auto last_size = slinky.Size();
    current_node = slinky.Delete(last_node);
    EXPECT_LT(slinky.Size(), last_size);
}

//! \test   DeletionFromHeadShouldDecrementCount
TEST_F(SlinkyTest, DeletionFromHeadShouldDecrementCount) {
    InsertNATO(2);

    auto last_size = slinky.Size();
    current_node = slinky.Delete();
    EXPECT_LT(slinky.Size(), last_size);
}

//! \test   ClearingListShouldReturnEmpty
TEST_F(SlinkyTest, ClearingListShouldReturnEmpty) {
    slinky.Clear();
    EXPECT_TRUE(slinky.IsEmpty());
}

//! \test   ListContentsShouldBeAlfaBravoCharlie
TEST_F(SlinkyTest, ListContentsShouldBeAlfaBravoCharlie) {
    InsertNATO(3);

    std::vector<std::string> expected{natos[0], natos[1], natos[2]};
    std::vector<std::string> abc = slinky.PrintList();
    EXPECT_THAT(abc, ::testing::Eq(expected));
}

//! \test   ListContentsAfterReversalShouldBeCharlieBravoAlfa
TEST_F(SlinkyTest, ListContentsAfterReversalShouldBeCharlieBravoAlfa) {
    InsertNATO(3);

    std::vector<std::string> expected{natos[2], natos[1], natos[0]};
    slinky.ReverseList();
    std::vector<std::string> cba = slinky.PrintList();
    EXPECT_THAT(cba, ::testing::Eq(expected));
}

//! \test   GetFromIndex1ShouldReturnBravo
TEST_F(SlinkyTest, GetFromIndex1ShouldReturnBravo) {
    InsertNATO(3);

    std::string gotten = slinky.Get(1);
    EXPECT_EQ(natos[1], gotten);
}

//! \test   ListContentsAfterAppendShouldBeAlfaBravoAlfa
TEST_F(SlinkyTest, ListContentsAfterAppendShouldBeAlfaBravoAlfa) {
    InsertNATO(2);

    std::vector<std::string> expected{natos[0], natos[1], natos[0]};

    slinky.Append(natos[0]);
    std::vector<std::string> aba = slinky.PrintList();
    EXPECT_THAT(aba, ::testing::Eq(expected));
}

//! \test   ListSizeShouldIncreaseAfterAppend
TEST_F(SlinkyTest, ListSizeShouldIncreaseAfterAppend) {
    InsertNATO(2);
    auto size2 = slinky.Size();

    slinky.Append(natos[2]);
    auto size3 = slinky.Size();

    EXPECT_GT(size3, size2);
}

//! \test   ListSizeShouldIncreaseAfterPrepend
TEST_F(SlinkyTest, ListSizeShouldIncreaseAfterPrepend) {
    auto size0 = slinky.Size();

    slinky.Prepend(natos[1]);
    auto size1 = slinky.Size();
    EXPECT_GT(size1, size0);
}

//! \test   ListContentsAfterPrependShouldBeCharlieBravoAlfa
TEST_F(SlinkyTest, ListContentsAfterPrependShouldBeCharlieBravoAlfa) {
    slinky.Prepend(natos[0]);
    slinky.Prepend(natos[1]);
    slinky.Prepend(natos[2]);

    std::vector<std::string> expected{natos[2], natos[1], natos[0]};
    std::vector<std::string> cba = slinky.PrintList();
    EXPECT_THAT(cba, ::testing::Eq(expected));
}

//! \test   FirstShouldReturnAlfa
TEST_F(SlinkyTest, FirstShouldReturnAlfa) {
    InsertNATO(5);

    EXPECT_EQ(natos[0], slinky.First());
}

//! \test   LastShouldReturnFoxtrot
TEST_F(SlinkyTest, LastShouldReturnFoxtrot) {
    InsertNATO(5);

    EXPECT_EQ(natos[4], slinky.Last());
}

//! \test   RemoveShouldReturnAlfaCharlie
TEST_F(SlinkyTest, RemoveShouldReturnAlfaCharlie) {
    InsertNATO(3);
    slinky.Remove(natos[1]);

    std::vector<std::string> expected{natos[0], natos[2]};
    std::vector<std::string> ac = slinky.PrintList();
    EXPECT_THAT(ac, ::testing::Eq(expected));
}

//! \test   RemoveFirstShouldReturnBravoCharlie
TEST_F(SlinkyTest, RemoveFirstShouldReturnBravoCharlie) {
    InsertNATO(3);
    slinky.RemoveFirst();

    std::vector<std::string> expected{natos[1], natos[2]};
    std::vector<std::string> ac = slinky.PrintList();
    EXPECT_THAT(ac, ::testing::Eq(expected));
}

//! \test   RemoveLastShouldReturnCharlieBravo
TEST_F(SlinkyTest, RemoveLastShouldReturnCharlieBravo) {
    slinky.Prepend(natos[0]);
    slinky.Prepend(natos[1]);
    slinky.Prepend(natos[2]);
    slinky.RemoveLast();

    std::vector<std::string> expected{natos[2], natos[1]};
    std::vector<std::string> cb = slinky.PrintList();
    EXPECT_THAT(cb, ::testing::Eq(expected));
}


//! \fn     main
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}