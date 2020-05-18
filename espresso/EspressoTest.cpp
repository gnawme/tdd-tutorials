/*! -------------------------------------------------------------------------*\
|   Postfix expression tree
\*---------------------------------------------------------------------------*/
#include "Espresso.h"

#include <gmock/gmock.h>
#include <iostream>
#include <string>
#include <vector>

/// \class  GraphisTest
class EspressoTest : public ::testing::Test {
public:
    void SetUp() override {}

    void LoadMultiOperatorExpression() {
        for (auto entry : wikieqn) {
            espresso.addSymbol(entry);
        }
    }

    void LoadSingleOperatorExpression() {
        for (auto entry : shorty) {
            espresso.addSymbol(entry);
        }
    }

    Espresso espresso;

    std::string shorty{"ab+"};

    std::string wikieqn{"ab+cde+**"};
};

/// \test   EmptyTreeShouldReturnEmpty
TEST_F(EspressoTest, EmptyTreeShouldReturnEmpty) {
    EXPECT_TRUE(espresso.isEmpty());
}

/// \test   SingleOperatorEquationShouldMatchExpected
TEST_F(EspressoTest, SingleOperatorEquationShouldMatchExpected) {
    LoadSingleOperatorExpression();
    EXPECT_FALSE(espresso.isEmpty());

    std::vector<char> compare{'a', 'b', '+'};

    espresso.traversePostorder();
    std::vector<char> expression = espresso.getTree();
    EXPECT_THAT(compare, ::testing::ContainerEq(expression));
}

/// \test   MultiOperatorExpressionShouldMatchExpected
TEST_F(EspressoTest, MultiOperatorExpressionShouldMatchExpected) {
    LoadMultiOperatorExpression();
    EXPECT_FALSE(espresso.isEmpty());

    std::vector<char> compare{'a', 'b', '+', 'c', 'd', 'e', '+', '*', '*'};

    espresso.traversePostorder();
    std::vector<char> expression = espresso.getTree();
    EXPECT_THAT(compare, ::testing::ContainerEq(expression));
}

///
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
