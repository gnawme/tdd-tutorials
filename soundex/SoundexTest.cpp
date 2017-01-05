/*---------------------------------------------------------------------------*\
|
\*---------------------------------------------------------------------------*/
#include "Soundex.h"
#include <gmock/gmock.h>

/*---------------------------------------------------------------------------*\
|
\*---------------------------------------------------------------------------*/
class SoundexEncodingTest: public ::testing::Test {
public:
    SoundexEncodingTest() {}

    Soundex mSoundex;
};

/*---------------------------------------------------------------------------*\
|
\*---------------------------------------------------------------------------*/
TEST_F(SoundexEncodingTest, RetainSoleLetterOfOneWord) {

    auto encoded = mSoundex.encode("A");
    ASSERT_EQ(encoded, "A000");
}

TEST_F(SoundexEncodingTest, PadsWithZerosToEnsureThreeDigits) {

    auto encoded = mSoundex.encode("I");
    ASSERT_EQ(encoded, "I000");
}

/*---------------------------------------------------------------------------*\
|
\*---------------------------------------------------------------------------*/
TEST_F(SoundexEncodingTest, ReplacesConsonantsWithAppropriateDigits) {

    auto encoded = mSoundex.encode("Ax");
    ASSERT_EQ(encoded, "A200");
}

/*---------------------------------------------------------------------------*\
|
\*---------------------------------------------------------------------------*/
TEST_F(SoundexEncodingTest, IgnoresNonAlphabetics) {

    auto encoded = mSoundex.encode("A#");
    ASSERT_EQ(encoded, "A000");
}

/*---------------------------------------------------------------------------*\
|
\*---------------------------------------------------------------------------*/
TEST_F(SoundexEncodingTest, LimitsLengthToFourCharacters) {

    auto encoded = mSoundex.encode("Evangelista");
    ASSERT_EQ(encoded.length(), 4);
}

/*---------------------------------------------------------------------------*\
|
\*---------------------------------------------------------------------------*/
TEST_F(SoundexEncodingTest, IgnoresVowelLikeLetters) {

    auto encoded = mSoundex.encode("Baeiouhycdl");
    ASSERT_EQ(encoded, "B234");
}

/*---------------------------------------------------------------------------*\
|
\*---------------------------------------------------------------------------*/
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}