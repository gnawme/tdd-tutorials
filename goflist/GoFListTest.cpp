#include "GoFList.hpp"

#include <gmock/gmock.h>

//! \struct GoFListTest
struct GoFListTest: public ::testing::Test
{
    virtual void SetUp()
    {}

    std::array<std::string, 26> natos{
        {
            "alfa", "bravo", "charlie", "delta", "echo", "foxtrot",
            "golf", "hotel", "india", "juliett", "kilo", "lima",
            "mike", "november", "oscar", "papa", "quebec", "romeo",
            "sierra", "tango", "uniform", "victor", "whiskey", "x-ray",
            "yankee", "zulu"
        }
    };

    void AppendNATO(int count)
    {
        for (auto i = 0; i < count; ++i) {
            goflist.Append(natos[i]);
        }
    }

    void PrependNATO(int count)
    {
        for (auto i = 0; i < count; ++i) {
            goflist.Prepend(natos[i]);
        }
    }

    GoFList<std::string>    goflist;
};

//! \test   InitialCountShouldBeZero
TEST_F(GoFListTest, InitialCountShouldBeZero) {
    EXPECT_EQ(0, goflist.Count());
}

//! \test   CountAfterAppendShouldBeGreater
TEST_F(GoFListTest, CountAfterAppendShouldBeGreater) {
    auto count0 = goflist.Count();
    AppendNATO(2);
    auto count2 = goflist.Count();
    EXPECT_GT(count2, count0);
}

//! \test   FirstShouldBeAlfaLastShouldBeDelta
TEST_F(GoFListTest, FirstShouldBeAlfaLastShouldBeDelta) {
    AppendNATO(4);
    EXPECT_EQ(natos[0], goflist.First());
    EXPECT_EQ(natos[3], goflist.Last());
}

//! \test   TopShouldReturnCharlie
TEST_F(GoFListTest, TopShouldReturnCharlie) {
    PrependNATO(3);
    EXPECT_EQ(natos[2], goflist.Top());
}

//! \fn     main
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}