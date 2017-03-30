/*! -------------------------------------------------------------------------*\
|   Maze generation by recursive backtracing
|   \see http://weblog.jamisbuck.org/2010/12/27/maze-generation-recursive-backtracking
\*---------------------------------------------------------------------------*/
#include "RBMaze.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>

//! \fn     RandomStart
//! \brief  Generates a random start value in [minval, maxval]
inline int RandomStart(int minval, int maxval)
{
    return minval + (std::rand() % (maxval - minval + 1));
}

//! \fn     main
int main()
{
    std::srand(std::time(0));

    RBMaze maze(8, 8 );

    auto cx = RandomStart(0, 8);
    auto cy = RandomStart(0, 8);
    std::cout << "Generating from " << cx << ", " << cy << std::endl;
    maze.CarvePassagesFrom(cx, cy);

    maze.PrintMaze();

    return 0;
}