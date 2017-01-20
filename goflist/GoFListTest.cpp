#include "GoFList.hpp"

#include <gmock/gmock.h>

//! \struct GoFListTest
struct GoFListTest: public ::testing::Test
{
    virtual void SetUp()
    {}

    GoFList<std::string>    goflist;
};

//! \test   InitialCountShouldBeZero
TEST_F(GoFListTest, InitialCountShouldBeZero) {
    EXPECT_EQ(0, goflist.Count());
}

//! \fn     main
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}