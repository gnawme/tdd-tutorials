/*! -------------------------------------------------------------------------*\
|   Maze generation by recursive backtracing
|   \see http://weblog.jamisbuck.org/2010/12/27/maze-generation-recursive-backtracking
\*---------------------------------------------------------------------------*/
#include "RBMaze.hpp"

#include <algorithm>
#include <iostream>
#include <random>


//! \fn     CheckInRange
bool CheckInRange(int number, int lower, int upper) {
    return (static_cast<unsigned int>(number - lower) <= (upper - lower));
}

//! \fn     DirY
int DirX(MazeDir dir) {
    switch (dir) {
    case MazeDir::MD_E:
        return 1;
        break;
    case MazeDir::MD_W:
        return -1;
        break;
    case MazeDir::MD_N:
    case MazeDir::MD_S:
        return 0;
        break;
    }
}

//! \fn     DirY
int DirY(MazeDir dir) {
    switch (dir) {
    case MazeDir::MD_N:
        return -1;
        break;
    case MazeDir::MD_S:
        return 1;
        break;
    case MazeDir::MD_E:
    case MazeDir::MD_W:
        return 0;
        break;
    }
}

//! \fn     Opposite
MazeDir Opposite(MazeDir dir) {
    switch (dir) {
    case MazeDir::MD_N:
        return MazeDir::MD_S;
        break;
    case MazeDir::MD_S:
        return MazeDir::MD_N;
        break;
    case MazeDir::MD_E:
        return MazeDir::MD_W;
        break;
    case MazeDir::MD_W:
        return MazeDir::MD_E;
        break;
    }
}

//! \fn     RBMaze::CarvePassagesFrom
void RBMaze::CarvePassagesFrom(int cx, int cy) {
    std::cout << "At " << cx << ", " << cy << std::endl;
    std::shuffle(m_dirs.begin(), m_dirs.end(), std::mt19937(std::random_device()()));

    for (auto dir : m_dirs) {
        auto nx = cx + DirX(dir);
        auto ny = cy + DirY(dir);

        if (IsValid(nx, ny)) {
            m_maze[cy][cx] |= int(dir);
            m_maze[ny][nx] |= int(Opposite(dir));
            CarvePassagesFrom(nx, ny);
        }
    }
}

//! \fn     RBMaze::IsValid
bool RBMaze::IsValid(int nx, int ny) {
    return (CheckInRange(nx, 0, GetXDim() - 1) && CheckInRange(ny, 0, GetYDim() - 1)
            && (m_maze[ny][nx] == 0));
}

//! \fn     RBMaze::PrintMaze
void RBMaze::PrintMaze() const {
    for (auto j = 0; j < GetYDim() - 1; ++j) {
        std::cout << "|";
        for (auto i = 0; i < GetXDim() - 1; ++i) {
            if (m_maze[j][i] & int(MazeDir::MD_S) != 0) {
                std::cout << " ";
            } else {
                std::cout << "_";
            }

            if (m_maze[j][i] & int(MazeDir::MD_E) != 0) {
                if ((m_maze[j][i] | m_maze[j][i + 1]) & int(MazeDir::MD_S) != 0) {
                    std::cout << " ";
                } else {
                    std::cout << "|";
                }
            }
        }
        std::cout << std::endl;
    }
}
