#include "Circula.h"

#include <array>
#include <gmock/gmock.h>
#include <string>
#include <vector>

//! \class  CirculaTest
class CirculaTest : public ::testing::Test
{
public:
    void SetUp() override
    {
    }

    Circula<std::string, 3> m_circula;
    std::vector<std::string> m_natos{
        "alfa", "bravo", "charlie", "delta", "echo"
    };
};

//! \test   EmptyBufferShouldReturnEmpty
TEST_F(CirculaTest, EmptyBufferShouldReturnEmpty)
{
    EXPECT_TRUE(m_circula.IsEmpty());
}

//! \test   PoppingFromAnEmptyBufferShouldThrow
TEST_F(CirculaTest, PoppingFromAnEmptyBufferShouldThrow)
{
    EXPECT_THROW(m_circula.Pop(), std::underflow_error);
}

//! \test   QueryingCapacityShouldReturnExpectedValue
TEST_F(CirculaTest, QueryingCapacityShouldReturnExpectedValue)
{
    EXPECT_EQ(3, m_circula.Capacity());
}

//! \test   PushingPastBufferCapacityShouldThrow
TEST_F(CirculaTest, PushingPastBufferCapacityShouldThrow)
{
    auto idx{0};
    m_circula.Push(m_natos[idx++]);
    m_circula.Push(m_natos[idx++]);
    m_circula.Push(m_natos[idx++]);
    EXPECT_THROW(m_circula.Push(m_natos[idx++]), std::overflow_error);
}

//! \test   NormalBufferOperationsShouldYieldExpectedResults
TEST_F(CirculaTest, NormalBufferOperationsShouldYieldExpectedResults)
{
    auto idx{0};
    m_circula.Push(m_natos[idx++]);
    m_circula.Push(m_natos[idx++]);
    m_circula.Push(m_natos[idx++]);

    EXPECT_EQ(m_natos[0], m_circula.Pop());

    m_circula.Push(m_natos[idx++]);
    EXPECT_EQ(m_natos[1], m_circula.Pop());
}

//! \fn     main
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}