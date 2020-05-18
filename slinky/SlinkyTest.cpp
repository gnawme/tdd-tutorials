#include "Slinky.h"

#include <array>
#include <gmock/gmock.h>
#include <string>
#include <vector>

using TStringVec = std::vector<std::string>;

/// \class  SlinkyTest
class SlinkyTest : public ::testing::Test {
public:
    void SetUp() override {
        slinky.clear();
    }

    void insertNATO(int count) {
        for (auto i = 0; i < count; ++i) {
            slinky.append(natos[i]);
        }
    }

    std::array<std::string, 26> natos{
            {"alfa",   "bravo",   "charlie", "delta",  "echo",   "foxtrot", "golf",
             "hotel",  "india",   "juliett", "kilo",   "lima",   "mike",    "november",
             "oscar",  "papa",    "quebec",  "romeo",  "sierra", "tango",   "uniform",
             "victor", "whiskey", "x-ray",   "yankee", "zulu"}};

    Slinky<std::string> slinky;
    ListNode<std::string>* currentNode;
};

/// \test   EmptyListShouldReturnEmpty
TEST_F(SlinkyTest, EmptyListShouldReturnEmpty) {
    EXPECT_TRUE(slinky.isEmpty());
}

/// \test   EmptyListShouldReturnSizeZero
TEST_F(SlinkyTest, EmptyListShouldReturnSizeZero) {
    EXPECT_EQ(slinky.size(), 0);
}

/// \test   InsertionShouldReturnSizeOne
TEST_F(SlinkyTest, InsertionShouldReturnSizeOne) {
    currentNode = slinky.insert(new ListNode<std::string>(natos[0]));
    EXPECT_EQ(slinky.size(), 1);
}

/// \test   InsertionShouldReturnSameNode
TEST_F(SlinkyTest, InsertionShouldReturnSameNode) {
    currentNode = slinky.insert(new ListNode<std::string>(natos[0]));
    auto newNode{new ListNode<std::string>(natos[1])};
    currentNode = slinky.insert(currentNode, newNode);
    EXPECT_EQ(currentNode, newNode);
}

/// \test   DeletionShouldDecrementCount
TEST_F(SlinkyTest, DeletionShouldDecrementCount) {
    auto lastNode{new ListNode<std::string>(natos[0])};
    currentNode = slinky.insert(lastNode);
    currentNode = slinky.insert(lastNode, new ListNode<std::string>(natos[1]));

    auto lastSize{slinky.size()};
    currentNode = slinky.deleteNode(lastNode);
    EXPECT_LT(slinky.size(), lastSize);
}

/// \test   DeletionFromHeadShouldDecrementCount
TEST_F(SlinkyTest, DeletionFromHeadShouldDecrementCount) {
    insertNATO(2);

    auto lastSize{slinky.size()};
    currentNode = slinky.deleteNode();
    EXPECT_LT(slinky.size(), lastSize);
}

/// \test   ClearingListShouldReturnEmpty
TEST_F(SlinkyTest, ClearingListShouldReturnEmpty) {
    slinky.clear();
    EXPECT_TRUE(slinky.isEmpty());
}

/// \test   ListContentsShouldBeAlfaBravoCharlie
TEST_F(SlinkyTest, ListContentsShouldBeAlfaBravoCharlie) {
    insertNATO(3);

    TStringVec expected{natos[0], natos[1], natos[2]};
    TStringVec abc{slinky._printList()};
    EXPECT_THAT(abc, ::testing::Eq(expected));
}

/// \test   ListContentsAfterReversalShouldBeCharlieBravoAlfa
TEST_F(SlinkyTest, ListContentsAfterReversalShouldBeCharlieBravoAlfa) {
    insertNATO(3);

    TStringVec expected{natos[2], natos[1], natos[0]};
    slinky.reverseList();
    TStringVec cba{slinky._printList()};
    EXPECT_THAT(cba, ::testing::Eq(expected));
}

/// \test   ListContentsAfterRecursiveReversalShouldBeCharlieBravoAlfa
TEST_F(SlinkyTest, ListContentsAfterRecursiveReversalShouldBeCharlieBravoAlfa) {
    insertNATO(3);

    TStringVec expected{natos[2], natos[1], natos[0]};
    slinky.reverse();
    TStringVec cba{slinky._printList()};
    EXPECT_THAT(cba, ::testing::Eq(expected));
}

/// \test   GetFromIndex1ShouldReturnBravo
TEST_F(SlinkyTest, GetFromIndex1ShouldReturnBravo) {
    insertNATO(3);

    std::string gotten{slinky.get(1)};
    EXPECT_EQ(natos[1], gotten);
}

/// \test   ListContentsAfterAppendShouldBeAlfaBravoAlfa
TEST_F(SlinkyTest, ListContentsAfterAppendShouldBeAlfaBravoAlfa) {
    insertNATO(2);

    TStringVec expected{natos[0], natos[1], natos[0]};

    slinky.append(natos[0]);
    TStringVec aba{slinky._printList()};
    EXPECT_THAT(aba, ::testing::Eq(expected));
}

/// \test   ListSizeShouldIncreaseAfterAppend
TEST_F(SlinkyTest, ListSizeShouldIncreaseAfterAppend) {
    insertNATO(2);
    auto size2{slinky.size()};

    slinky.append(natos[2]);
    auto size3{slinky.size()};

    EXPECT_GT(size3, size2);
}

/// \test   ListSizeShouldIncreaseAfterPrepend
TEST_F(SlinkyTest, ListSizeShouldIncreaseAfterPrepend) {
    auto size0{slinky.size()};

    slinky.prepend(natos[1]);
    auto size1{slinky.size()};
    EXPECT_GT(size1, size0);
}

/// \test   ListContentsAfterPrependShouldBeCharlieBravoAlfa
TEST_F(SlinkyTest, ListContentsAfterPrependShouldBeCharlieBravoAlfa) {
    slinky.prepend(natos[0]);
    slinky.prepend(natos[1]);
    slinky.prepend(natos[2]);

    TStringVec expected{natos[2], natos[1], natos[0]};
    TStringVec cba{slinky._printList()};
    EXPECT_THAT(cba, ::testing::Eq(expected));
}

/// \test   FirstShouldReturnAlfa
TEST_F(SlinkyTest, FirstShouldReturnAlfa) {
    insertNATO(5);

    EXPECT_EQ(natos[0], slinky.first());
}

/// \test   LastShouldReturnFoxtrot
TEST_F(SlinkyTest, LastShouldReturnFoxtrot) {
    insertNATO(5);

    EXPECT_EQ(natos[4], slinky.Last());
}

/// \test   RemoveShouldReturnAlfaCharlie
TEST_F(SlinkyTest, RemoveShouldReturnAlfaCharlie) {
    insertNATO(3);
    slinky.Remove(natos[1]);

    TStringVec expected{natos[0], natos[2]};
    TStringVec ac{slinky._printList()};
    EXPECT_THAT(ac, ::testing::Eq(expected));
}

/// \test   RemoveFirstShouldReturnBravoCharlie
TEST_F(SlinkyTest, RemoveFirstShouldReturnBravoCharlie) {
    insertNATO(3);
    slinky.removeFirst();

    TStringVec expected{natos[1], natos[2]};
    TStringVec ac{slinky._printList()};
    EXPECT_THAT(ac, ::testing::Eq(expected));
}

/// \test   RemoveLastShouldReturnCharlieBravo
TEST_F(SlinkyTest, RemoveLastShouldReturnCharlieBravo) {
    slinky.prepend(natos[0]);
    slinky.prepend(natos[1]);
    slinky.prepend(natos[2]);
    slinky.removeLast();

    TStringVec expected{natos[2], natos[1]};
    TStringVec cb{slinky._printList()};
    EXPECT_THAT(cb, ::testing::Eq(expected));
}

/// \test   GetAndRemoveFirstShouldCopyTheList
TEST_F(SlinkyTest, GetAndRemoveFirstShouldCopyTheList) {
    insertNATO(5);
    TStringVec abcde = slinky._printList();

    TStringVec contents;
    auto fullsize{slinky.size()};
    for (auto i = 0; i < fullsize; ++i) {
        contents.push_back(slinky.first());
        slinky.removeFirst();
    }

    EXPECT_THAT(contents, ::testing::Eq(abcde));
}

/// \test   CopyConstructorShouldReturnIdenticalList
TEST_F(SlinkyTest, CopyConstructorShouldReturnIdenticalList) {
    insertNATO(5);
    TStringVec original{slinky._printList()};

    Slinky<std::string> clone(slinky);
    TStringVec clonewars{clone._printList()};

    EXPECT_THAT(original, ::testing::Eq(clonewars));
}

/// \test   AssignmentOperatorShouldReturnIdenticalList
TEST_F(SlinkyTest, AssignmentOperatorShouldReturnIdenticalList) {
    insertNATO(5);
    TStringVec original{slinky._printList()};

    Slinky<std::string> clone;
    for (auto i = 0; i < 3; ++i) {
        clone.append(natos[i]);
    }

    clone = slinky;
    TStringVec clonewars{clone._printList()};

    EXPECT_THAT(original, ::testing::Eq(clonewars));
}

/// \test   MoveConstructorShouldReturnIdenticalList
TEST_F(SlinkyTest, MoveConstructorShouldReturnIdenticalList) {
    insertNATO(5);
    TStringVec original{slinky._printList()};

    Slinky<std::string> clone(std::move(slinky));
    TStringVec clonewars{clone._printList()};

    EXPECT_THAT(original, ::testing::Eq(clonewars));
}

/// \test   MoveAssignmentOperatorShouldReturnIdenticalList
TEST_F(SlinkyTest, MoveAssignmentOperatorShouldReturnIdenticalList) {
    insertNATO(5);
    TStringVec original{slinky._printList()};

    Slinky<std::string> clone;
    for (auto i = 0; i < 3; ++i) {
        clone.append(natos[i]);
    }

    clone = std::move(slinky);
    TStringVec clonewars{clone._printList()};

    EXPECT_THAT(original, ::testing::Eq(clonewars));
}

/// \test   RemoveAllShouldLeaveEmptyList
TEST_F(SlinkyTest, RemoveAllShouldLeaveEmptyList) {
    insertNATO(5);
    slinky.RemoveAll();

    EXPECT_TRUE(slinky.isEmpty());
}

/// \test   SearchForEchoShouldReturnEcho
TEST_F(SlinkyTest, SearchForEchoShouldReturnEcho) {
    insertNATO(8);
    ListNode<std::string>* echo{slinky.search(std::string("echo"))};

    EXPECT_EQ(std::string("echo"), echo->data);
}

///
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}