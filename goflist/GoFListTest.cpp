#include "GoFList.hpp"

#include <gmock/gmock.h>

#include <utility>

/// \struct GoFListTest
struct GoFListTest : public ::testing::Test {
    void SetUp() override {}

    std::array<std::string, 26> natos{
            {"alfa",   "bravo",   "charlie", "delta",  "echo",   "foxtrot", "golf",
             "hotel",  "india",   "juliett", "kilo",   "lima",   "mike",    "november",
             "oscar",  "papa",    "quebec",  "romeo",  "sierra", "tango",   "uniform",
             "victor", "whiskey", "x-ray",   "yankee", "zulu"}};

    void AppendNATO(int count) {
        for (auto i = 0; i < count; ++i) {
            goflist.append(natos[i]);
        }
    }

    void PrependNATO(int count) {
        for (auto i = 0; i < count; ++i) {
            goflist.prepend(natos[i]);
        }
    }

    GoFList<std::string> goflist;
};

/// \test   InitialCountShouldBeZero
TEST_F(GoFListTest, InitialCountShouldBeZero) {
    EXPECT_EQ(0, goflist.count());
}

/// \test   CountAfterAppendShouldBeGreater
TEST_F(GoFListTest, CountAfterAppendShouldBeGreater) {
    auto count0{goflist.count()};
    AppendNATO(2);
    auto count2{goflist.count()};
    EXPECT_GT(count2, count0);
}

/// \test   FirstShouldBeAlfaLastShouldBeDelta
TEST_F(GoFListTest, FirstShouldBeAlfaLastShouldBeDelta) {
    AppendNATO(4);
    EXPECT_EQ(natos[0], goflist.first());
    EXPECT_EQ(natos[3], goflist.Last());
}

/// \test   TopShouldReturnCharlie
TEST_F(GoFListTest, TopShouldReturnCharlie) {
    PrependNATO(3);
    EXPECT_EQ(natos[2], goflist.Top());
}

/// \test   PushPushShouldReturnAlfaAlfa
TEST_F(GoFListTest, PushPushShouldReturnAlfaAlfa) {
    goflist.push(natos[0]);
    goflist.push(natos[0]);

    std::vector<std::string> expected{natos[0], natos[0]};
    std::vector<std::string> aa{goflist._printList()};

    EXPECT_THAT(expected, ::testing::Eq(aa));
}

/// \test   ThreePushesAndPopShouldReturnBravoAlfa
TEST_F(GoFListTest, ThreePushesAndPopShouldReturnBravoAlfa) {
    for (auto i = 0; i < 3; ++i) {
        goflist.push(natos[i]);
    }

    std::string whatsit{goflist.pop()};
    EXPECT_EQ(natos[2], whatsit);

    std::vector<std::string> expected{natos[1], natos[0]};
    std::vector<std::string> ba{goflist._printList()};
    EXPECT_THAT(expected, ::testing::Eq(ba));
}

///
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}