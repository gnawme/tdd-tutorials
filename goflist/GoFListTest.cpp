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

    GoFList<std::string>    goflist;
};

//! \test   InitialCountShouldBeZero
TEST_F(GoFListTest, InitialCountShouldBeZero) {
    EXPECT_EQ(0, goflist.Count());
}

//! \test   CountAfterAppendShouldBeGreater
TEST_F(GoFListTest, CountAfterAppendShouldBeGreater) {
    auto count0 = goflist.Count();
    goflist.Append(natos[0]);
    goflist.Append(natos[1]);

    auto count2 = goflist.Count();
    EXPECT_GT(count2, count0);
}

//! \fn     main
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}