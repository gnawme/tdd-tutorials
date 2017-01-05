/*---------------------------------------------------------------------------*\
|
\*---------------------------------------------------------------------------*/
#ifndef BOWLING_GAME_BOWLINGGAMETEST_H
#define BOWLING_GAME_BOWLINGGAMETEST_H

#include <gmock/gmock.h>

#include "BowlingGame.h"


/*---------------------------------------------------------------------------*\
|
\*---------------------------------------------------------------------------*/
class BowlingGameTest: public ::testing::Test {
public:
    BowlingGameTest() {}

    virtual void SetUp() {}

    BowlingGame mBowlingGame;

    void rollMany(int numIter, int numPins);
    void rollSpare();
};


#endif //BOWLING_GAME_BOWLINGGAMETEST_H
