/*! -------------------------------------------------------------------------*\
|   Maze generation by recursive backtracing
|   \see http://weblog.jamisbuck.org/2010/12/27/maze-generation-recursive-backtracking
\*---------------------------------------------------------------------------*/
#ifndef MAZEGEN_RBMAZE_HPP
#define MAZEGEN_RBMAZE_HPP
#include <memory>
#include <vector>

enum MazeDirs
{
    e_N = 1,
    e_S = 2,
    e_E = 4,
    e_W = 8
};

class RBMaze
{
public:
    //! \fn     RBMaze
    RBMaze(int xdim, int ydim)
        : m_xdim(xdim)
        , m_ydim(ydim)
    {
        std::vector<int> rows(ydim, 0);
        std::vector<std::vector<int>> maze(xdim, rows);
        m_maze = maze;
    }

    //! \fn     CarvePassagesFrom
    void CarvePassagesFrom(int cx, int cy);

    //! \fn     GetXDim
    int GetXDim() const
    {
        return m_xdim;
    }

    //! \fn     GetYDim
    int GetYDim() const
    {
        return m_ydim;
    }

    //! \fn     PrintMaze
    void PrintMaze() const;

private:
    bool IsValid(int nx, int ny);

    int m_xdim;
    int m_ydim;
    std::vector<std::vector<int>> m_maze;
    std::vector<MazeDirs> m_dirs{e_N, e_S, e_E, e_W};
};

#endif // MAZEGEN_RBMAZE_HPP
