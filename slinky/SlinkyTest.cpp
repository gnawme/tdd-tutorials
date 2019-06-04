#include "Slinky.hpp"

#include <array>
#include <gmock/gmock.h>
#include <string>
#include <vector>

using TStringVec = std::vector<std::string>;

//! \class  SlinkyTest
class SlinkyTest : public ::testing::Test
{
public:
    void SetUp() override
    {
        slinky.Clear();
    }

    void InsertNATO(int count)
    {
        for (auto i = 0; i < count; ++i)
        {
            slinky.Append(natos[i]);
        }
    }

    std::array<std::string, 26> natos{
        {"alfa",   "bravo",   "charlie", "delta",  "echo",   "foxtrot", "golf",
         "hotel",  "india",   "juliett", "kilo",   "lima",   "mike",    "november",
         "oscar",  "papa",    "quebec",  "romeo",  "sierra", "tango",   "uniform",
         "victor", "whiskey", "x-ray",   "yankee", "zulu"}};

    Slinky<std::string> slinky;
    ListNode<std::string>* current_node;
};

//! \test   EmptyListShouldReturnEmpty
TEST_F(SlinkyTest, EmptyListShouldReturnEmpty)
{
    EXPECT_TRUE(slinky.IsEmpty());
}

//! \test   EmptyListShouldReturnSizeZero
TEST_F(SlinkyTest, EmptyListShouldReturnSizeZero)
{
    EXPECT_EQ(slinky.Size(), 0);
}

//! \test   InsertionShouldReturnSizeOne
TEST_F(SlinkyTest, InsertionShouldReturnSizeOne)
{
    current_node = slinky.Insert(new ListNode<std::string>(natos[0]));
    EXPECT_EQ(slinky.Size(), 1);
}

//! \test   InsertionShouldReturnSameNode
TEST_F(SlinkyTest, InsertionShouldReturnSameNode)
{
    current_node                    = slinky.Insert(new ListNode<std::string>(natos[0]));
    ListNode<std::string>* new_node = new ListNode<std::string>(natos[1]);
    current_node                    = slinky.Insert(current_node, new_node);
    EXPECT_EQ(current_node, new_node);
}

//! \test   DeletionShouldDecrementCount
TEST_F(SlinkyTest, DeletionShouldDecrementCount)
{
    ListNode<std::string>* last_node = new ListNode<std::string>(natos[0]);
    current_node                     = slinky.Insert(last_node);
    current_node = slinky.Insert(last_node, new ListNode<std::string>(natos[1]));

    auto last_size = slinky.Size();
    current_node   = slinky.Delete(last_node);
    EXPECT_LT(slinky.Size(), last_size);
}

//! \test   DeletionFromHeadShouldDecrementCount
TEST_F(SlinkyTest, DeletionFromHeadShouldDecrementCount)
{
    InsertNATO(2);

    auto last_size = slinky.Size();
    current_node   = slinky.Delete();
    EXPECT_LT(slinky.Size(), last_size);
}

//! \test   ClearingListShouldReturnEmpty
TEST_F(SlinkyTest, ClearingListShouldReturnEmpty)
{
    slinky.Clear();
    EXPECT_TRUE(slinky.IsEmpty());
}

//! \test   ListContentsShouldBeAlfaBravoCharlie
TEST_F(SlinkyTest, ListContentsShouldBeAlfaBravoCharlie)
{
    InsertNATO(3);

    TStringVec expected{natos[0], natos[1], natos[2]};
    TStringVec abc = slinky.PrintList();
    EXPECT_THAT(abc, ::testing::Eq(expected));
}

//! \test   ListContentsAfterReversalShouldBeCharlieBravoAlfa
TEST_F(SlinkyTest, ListContentsAfterReversalShouldBeCharlieBravoAlfa)
{
    InsertNATO(3);

    TStringVec expected{natos[2], natos[1], natos[0]};
    slinky.ReverseList();
    TStringVec cba = slinky.PrintList();
    EXPECT_THAT(cba, ::testing::Eq(expected));
}

//! \test   ListContentsAfterRecursiveReversalShouldBeCharlieBravoAlfa
TEST_F(SlinkyTest, ListContentsAfterRecursiveReversalShouldBeCharlieBravoAlfa)
{
    InsertNATO(3);

    TStringVec expected{natos[2], natos[1], natos[0]};
    slinky.Reverse();
    TStringVec cba = slinky.PrintList();
    EXPECT_THAT(cba, ::testing::Eq(expected));
}

//! \test   GetFromIndex1ShouldReturnBravo
TEST_F(SlinkyTest, GetFromIndex1ShouldReturnBravo)
{
    InsertNATO(3);

    std::string gotten = slinky.Get(1);
    EXPECT_EQ(natos[1], gotten);
}

//! \test   ListContentsAfterAppendShouldBeAlfaBravoAlfa
TEST_F(SlinkyTest, ListContentsAfterAppendShouldBeAlfaBravoAlfa)
{
    InsertNATO(2);

    TStringVec expected{natos[0], natos[1], natos[0]};

    slinky.Append(natos[0]);
    TStringVec aba = slinky.PrintList();
    EXPECT_THAT(aba, ::testing::Eq(expected));
}

//! \test   ListSizeShouldIncreaseAfterAppend
TEST_F(SlinkyTest, ListSizeShouldIncreaseAfterAppend)
{
    InsertNATO(2);
    auto size2 = slinky.Size();

    slinky.Append(natos[2]);
    auto size3 = slinky.Size();

    EXPECT_GT(size3, size2);
}

//! \test   ListSizeShouldIncreaseAfterPrepend
TEST_F(SlinkyTest, ListSizeShouldIncreaseAfterPrepend)
{
    auto size0 = slinky.Size();

    slinky.Prepend(natos[1]);
    auto size1 = slinky.Size();
    EXPECT_GT(size1, size0);
}

//! \test   ListContentsAfterPrependShouldBeCharlieBravoAlfa
TEST_F(SlinkyTest, ListContentsAfterPrependShouldBeCharlieBravoAlfa)
{
    slinky.Prepend(natos[0]);
    slinky.Prepend(natos[1]);
    slinky.Prepend(natos[2]);

    TStringVec expected{natos[2], natos[1], natos[0]};
    TStringVec cba = slinky.PrintList();
    EXPECT_THAT(cba, ::testing::Eq(expected));
}

//! \test   FirstShouldReturnAlfa
TEST_F(SlinkyTest, FirstShouldReturnAlfa)
{
    InsertNATO(5);

    EXPECT_EQ(natos[0], slinky.First());
}

//! \test   LastShouldReturnFoxtrot
TEST_F(SlinkyTest, LastShouldReturnFoxtrot)
{
    InsertNATO(5);

    EXPECT_EQ(natos[4], slinky.Last());
}

//! \test   RemoveShouldReturnAlfaCharlie
TEST_F(SlinkyTest, RemoveShouldReturnAlfaCharlie)
{
    InsertNATO(3);
    slinky.Remove(natos[1]);

    TStringVec expected{natos[0], natos[2]};
    TStringVec ac = slinky.PrintList();
    EXPECT_THAT(ac, ::testing::Eq(expected));
}

//! \test   RemoveFirstShouldReturnBravoCharlie
TEST_F(SlinkyTest, RemoveFirstShouldReturnBravoCharlie)
{
    InsertNATO(3);
    slinky.RemoveFirst();

    TStringVec expected{natos[1], natos[2]};
    TStringVec ac = slinky.PrintList();
    EXPECT_THAT(ac, ::testing::Eq(expected));
}

//! \test   RemoveLastShouldReturnCharlieBravo
TEST_F(SlinkyTest, RemoveLastShouldReturnCharlieBravo)
{
    slinky.Prepend(natos[0]);
    slinky.Prepend(natos[1]);
    slinky.Prepend(natos[2]);
    slinky.RemoveLast();

    TStringVec expected{natos[2], natos[1]};
    TStringVec cb = slinky.PrintList();
    EXPECT_THAT(cb, ::testing::Eq(expected));
}

//! \test   GetAndRemoveFirstShouldCopyTheList
TEST_F(SlinkyTest, GetAndRemoveFirstShouldCopyTheList)
{
    InsertNATO(5);
    TStringVec abcde = slinky.PrintList();

    TStringVec contents;
    auto fullsize = slinky.Size();
    for (auto i = 0; i < fullsize; ++i)
    {
        contents.push_back(slinky.First());
        slinky.RemoveFirst();
    }

    EXPECT_THAT(contents, ::testing::Eq(abcde));
}

//! \test   CopyConstructorShouldReturnIdenticalList
TEST_F(SlinkyTest, CopyConstructorShouldReturnIdenticalList)
{
    InsertNATO(5);
    TStringVec original = slinky.PrintList();

    Slinky<std::string> clone(slinky);
    TStringVec clonewars = clone.PrintList();

    EXPECT_THAT(original, ::testing::Eq(clonewars));
}

//! \test   AssignmentOperatorShouldReturnIdenticalList
TEST_F(SlinkyTest, AssignmentOperatorShouldReturnIdenticalList)
{
    InsertNATO(5);
    TStringVec original = slinky.PrintList();

    Slinky<std::string> clone;
    for (auto i = 0; i < 3; ++i)
    {
        clone.Append(natos[i]);
    }

    clone                = slinky;
    TStringVec clonewars = clone.PrintList();

    EXPECT_THAT(original, ::testing::Eq(clonewars));
}

//! \test   MoveConstructorShouldReturnIdenticalList
TEST_F(SlinkyTest, MoveConstructorShouldReturnIdenticalList)
{
    InsertNATO(5);
    TStringVec original = slinky.PrintList();

    Slinky<std::string> clone(std::move(slinky));
    TStringVec clonewars = clone.PrintList();

    EXPECT_THAT(original, ::testing::Eq(clonewars));
}

//! \test   MoveAssignmentOperatorShouldReturnIdenticalList
TEST_F(SlinkyTest, MoveAssignmentOperatorShouldReturnIdenticalList)
{
    InsertNATO(5);
    TStringVec original = slinky.PrintList();

    Slinky<std::string> clone;
    for (auto i = 0; i < 3; ++i)
    {
        clone.Append(natos[i]);
    }

    clone                = std::move(slinky);
    TStringVec clonewars = clone.PrintList();

    EXPECT_THAT(original, ::testing::Eq(clonewars));
}

//! \test   RemoveAllShouldLeaveEmptyList
TEST_F(SlinkyTest, RemoveAllShouldLeaveEmptyList)
{
    InsertNATO(5);
    slinky.RemoveAll();

    EXPECT_TRUE(slinky.IsEmpty());
}

//! \test   SearchForEchoShouldReturnEcho
TEST_F(SlinkyTest, SearchForEchoShouldReturnEcho)
{
    InsertNATO(8);
    ListNode<std::string>* echo = slinky.Search(std::string("echo"));

    EXPECT_EQ(std::string("echo"), echo->data);
}

//! \fn     main
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}