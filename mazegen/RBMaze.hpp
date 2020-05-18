/*! -------------------------------------------------------------------------*\
|   Maze generation by recursive backtracing
|   \see http://weblog.jamisbuck.org/2010/12/27/maze-generation-recursive-backtracking
\*---------------------------------------------------------------------------*/
#pragma once
#include <memory>
#include <vector>

enum MazeDir { MD_N = 1, MD_S = 2, MD_E = 4, MD_W = 8 };

class RBMaze {
public:
    //! \fn     RBMaze
    RBMaze(int xdim, int ydim) : m_xdim(xdim), m_ydim(ydim) {
        std::vector<int> rows(ydim, 0);
        std::vector<std::vector<int>> maze(xdim, rows);
        m_maze = maze;
    }

    //! \fn     CarvePassagesFrom
    void CarvePassagesFrom(int cx, int cy);

    //! \fn     GetXDim
    [[nodiscard]] int GetXDim() const {
        return m_xdim;
    }

    //! \fn     GetYDim
    [[nodiscard]] int GetYDim() const {
        return m_ydim;
    }

    //! \fn     PrintMaze
    void PrintMaze() const;

private:
    bool IsValid(int nx, int ny);

    int m_xdim;
    int m_ydim;
    std::vector<std::vector<int>> m_maze;
    std::vector<MazeDir> m_dirs{MD_N, MD_S, MD_E, MD_W};
};
