/*! -------------------------------------------------------------------------*\
|   Postfix expression tree
\*---------------------------------------------------------------------------*/
#include "Espresso.hpp"

#include <gmock/gmock.h>
#include <iostream>
#include <string>
#include <vector>

//! \class  GraphisTest
class EspressoTest: public ::testing::Test
{
public:
    virtual void SetUp() {

    }

    void LoadMultiOperatorExpression()
    {
        for (auto entry : wikieqn) {
            espresso.AddSymbol(entry);
        }
    }

    void LoadSingleOperatorExpression()
    {
        for (auto entry : shorty) {
            espresso.AddSymbol(entry);
        }
    }

    Espresso espresso;

    std::string shorty{
        "ab+"
    };

    std::string wikieqn{
        "ab+cde+**"
    };
};

//! \test   EmptyTreeShouldReturnEmpty
TEST_F(EspressoTest, EmptyTreeShouldReturnEmpty) {
    EXPECT_TRUE(espresso.IsEmpty());
}

//! \test   SingleOperatorEquationShouldMatchExpected
TEST_F(EspressoTest, SingleOperatorEquationShouldMatchExpected) {
    LoadSingleOperatorExpression();
    EXPECT_FALSE(espresso.IsEmpty());

    std::vector<char> compare{
        'a', 'b', '+'
    };

    espresso.TraversePostorder();
    std::vector<char> expression = espresso.GetTree();
    EXPECT_THAT(compare, ::testing::ContainerEq(expression));
}

//! \test   MultiOperatorExpressionShouldMatchExpected
TEST_F(EspressoTest, MultiOperatorExpressionShouldMatchExpected) {
    LoadMultiOperatorExpression();
    EXPECT_FALSE(espresso.IsEmpty());

    std::vector<char> compare{
        'a', 'b', '+', 'c', 'd', 'e', '+', '*', '*'
    };

    espresso.TraversePostorder();
    std::vector<char> expression = espresso.GetTree();
    EXPECT_THAT(compare, ::testing::ContainerEq(expression));
}

//! \fn     main
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
