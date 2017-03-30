/*! -------------------------------------------------------------------------*\
|   Maze generation by recursive backtracing
|   \see http://weblog.jamisbuck.org/2010/12/27/maze-generation-recursive-backtracking
\*---------------------------------------------------------------------------*/
#include "RBMaze.hpp"

#include <algorithm>
#include <iostream>

//! \fn     CheckInRange
bool CheckInRange(int number, int lower, int upper)
{
    return (static_cast<unsigned int>(number - lower) <= (upper - lower));
}

//! \fn     DirY
int DirX(MazeDirs dir)
{
    switch (dir) {
        case MazeDirs::e_E:
            return 1;
            break;
        case MazeDirs::e_W:
            return -1;
            break;
        case MazeDirs::e_N:
        case MazeDirs::e_S:
            return 0;
            break;
    }
}

//! \fn     DirY
int DirY(MazeDirs dir)
{
    switch (dir) {
        case MazeDirs::e_N:
            return -1;
            break;
        case MazeDirs::e_S:
            return 1;
            break;
        case MazeDirs::e_E:
        case MazeDirs::e_W:
            return 0;
            break;
    }
}

//! \fn     Opposite
MazeDirs Opposite(MazeDirs dir)
{
    switch (dir) {
        case MazeDirs::e_N:
            return MazeDirs::e_S;
        break;
        case MazeDirs::e_S:
            return MazeDirs::e_N;
            break;
        case MazeDirs::e_E:
            return MazeDirs::e_W;
            break;
        case MazeDirs::e_W:
            return MazeDirs::e_E;
            break;
    }
}


//! \fn     RBMaze::CarvePassagesFrom
void RBMaze::CarvePassagesFrom(int cx, int cy)
{
    std::cout << "At " << cx << ", " << cy << std::endl;
    std::random_shuffle(m_dirs.begin(), m_dirs.end());

    for (auto dir : m_dirs) {
        auto nx = cx + DirX(dir);
        auto ny = cy + DirY(dir);

        if (IsValid(nx, ny)) {
            m_maze[cy][cx] |= dir;
            m_maze[ny][nx] |= Opposite(dir);
            CarvePassagesFrom(nx, ny);
        }
    }
}

//! \fn     RBMaze::IsValid
bool RBMaze::IsValid(int nx, int ny)
{
    return (
        CheckInRange(nx, 0, GetXDim() - 1) &&
        CheckInRange(ny, 0, GetYDim() - 1) &&
        (m_maze[ny][nx] == 0));
}

//! \fn     RBMaze::PrintMaze
void RBMaze::PrintMaze() const
{
    for (auto j = 0; j < GetYDim() - 1; ++j) {
        std::cout << "|";
        for (auto i = 0; i < GetXDim() - 1; ++i) {
            if (m_maze[j][i] & MazeDirs::e_S != 0) {
                std::cout << " ";
            } else {
                std::cout << "_";
            }

            if (m_maze[j][i] & MazeDirs::e_E != 0) {
                if ((m_maze[j][i] | m_maze[j][i+1]) & MazeDirs::e_S != 0) {
                    std::cout << " ";
                } else {
                    std::cout << "|";
                }
            }
        }
        std::cout << std::endl;
    }
}
