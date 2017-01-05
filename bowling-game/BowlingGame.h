/*---------------------------------------------------------------------------*\
|
\*---------------------------------------------------------------------------*/
#ifndef BOWLING_GAME_BOWLINGGAME_H
#define BOWLING_GAME_BOWLINGGAME_H

#include <array>

namespace
{
    const int BOWLING_NUM_FRAMES = 10;
    const int BOWLING_NUM_ROLLS = 21;
}

class BowlingGame {
public:
    BowlingGame()
    : mCurrentRoll(0)
    , mScore(0)
    {}

    void roll(int pins)
    {
        mRolls[mCurrentRoll++] = pins;
    }

    int score() {
        mScore = 0;
        int frameIndex = 0;
        for (int i = 0; i < BOWLING_NUM_FRAMES; ++i) {
            if (isSpare(frameIndex)) {
                mScore += 10 + mRolls[frameIndex + 2];
            } else {
                mScore += mRolls[frameIndex] + mRolls[frameIndex + 1];
            }
            frameIndex += 2;
        }
        return mScore;
    }

private:
    bool isSpare(int frameIndex)
    {
        return (mRolls[frameIndex] + mRolls[frameIndex + 1] == 10);
    }

    int                                 mCurrentRoll;
    std::array<int, BOWLING_NUM_ROLLS>  mRolls;
    int                                 mScore;


};


#endif //BOWLING_GAME_BOWLINGGAME_H
