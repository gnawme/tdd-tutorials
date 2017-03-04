/*! -------------------------------------------------------------------------*\
|   Adjacency list graph representation
|   \see http://www.geeksforgeeks.org/graph-and-its-representations/
\*---------------------------------------------------------------------------*/
#ifndef GRAPHIS_GRAPHIS_HPP
#define GRAPHIS_GRAPHIS_HPP

#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <vector>

//! \struct AdjacencyNode
template<typename DataT>
struct AdjacencyNode
{
    //! \fn     AdjacencyNode::AdjacencyNode
    AdjacencyNode(DataT dest)
        : dest(dest)
        , weight(0)
    {}

    //! \fn     AdjacencyNode::AdjacencyNode
    AdjacencyNode(DataT dest, int weight)
        : dest(dest)
        , weight(weight)
    {}

    DataT dest;
    int weight;
};

//! \enum   VisitedState
enum VisitedState
{
    e_undiscovered,
    e_discovered,
    e_processed
};

template<typename DataT>
class Graphis;

template<typename DataT>
using AdjacencyList = std::list<AdjacencyNode<DataT>>;

template<typename DataT>
using EdgeList = std::map<DataT, AdjacencyList<DataT>>;

template<typename DataT>
using DegreeList = std::map<DataT, int>;

template<typename DataT>
using TraversedList = std::map<DataT, VisitedState>;

template<typename DataT>
using ParentList = std::map<DataT, DataT>;

template<typename DataT>
using ComponentList = std::map<int, std::vector<DataT>>;

template<typename DataT>
using EntryList = std::map<DataT, std::pair<int, int>>;

template<typename DataT>
using ProcVertexFn = void (*)(Graphis<DataT>&, DataT);

template<typename DataT>
using ProcEdgeFn = void (*)(Graphis<DataT>&, DataT, DataT);

//! fn      ProcessVertexEarly
template<typename DataT>
void ProcessVertexEarly(Graphis<DataT>& graph, DataT vertex)
{}

//! fn      ProcessVertexLate
template<typename DataT>
void ProcessVertexLate(Graphis<DataT>& graph, DataT vertex)
{}

//! \fn     ProcessEdge
template<typename DataT>
void ProcessEdge(Graphis<DataT>& graph, DataT v1, DataT v2)
{}

//! class   Graphis
template<typename DataT>
class Graphis
{
public:
    //! \fn     Graphis::Graphis
    Graphis(bool is_directed = false)
    : m_num_vertices(0)
    , m_num_edges(0)
    , m_is_directed(is_directed)
    , m_terminate(false)
    , m_vertex_early(ProcessVertexEarly)
    , m_vertex_late(ProcessVertexLate)
    , m_edge_proc(ProcessEdge)
    {}

    //! \fn     Graphis::Graphis
    Graphis(int num_vertices, bool is_directed)
    : m_num_vertices(num_vertices)
    , m_num_edges(0)
    , m_is_directed(is_directed)
    , m_terminate(false)
    , m_vertex_early(ProcessVertexEarly)
    , m_vertex_late(ProcessVertexLate)
    , m_edge_proc(ProcessEdge)
    {}

    //! \fn     AddEdge
    void AddEdge(DataT src, DataT dst)
    {
        // Add edge from src to dst
        DoAddEdge(src, dst);

        // Add edge from dst to src for undirected graph
        if (!m_is_directed) {
            DoAddEdge(dst, src);
        }
    }

    //! \fn     BreadthFirstSearch
    //! \brief  Uses external TraversedList
    std::vector<DataT> BreadthFirstSearch(DataT root, TraversedList<DataT>& discovered)
    {
        std::queue<DataT> kew;
        discovered.at(root) = e_discovered;
        kew.push(root);

        std::vector<DataT> bfs;
        while (!kew.empty()) {
            DataT current_vertex = kew.front();
            bfs.push_back(current_vertex);
            kew.pop();
            discovered.at(current_vertex) = e_processed;
            m_vertex_early(*this, current_vertex);

            std::vector<DataT> adjlist = GetAdjacencyList(current_vertex);
            for (auto vert : adjlist) {
                if ((discovered.at(vert) != e_processed) || IsDirected()) {
                }

                if (discovered.at(vert) == e_undiscovered) {
                    discovered.at(vert) = e_discovered;
                    kew.push(vert);
                    m_parents.insert(std::make_pair(vert, current_vertex));
                }
            }

            m_vertex_late(*this, current_vertex);
        }

        return bfs;
    }

    //! \fn     BreadthFirstSearch
    //! \see    http://www.geeksforgeeks.org/breadth-first-traversal-for-a-graph/ or http://www.algorist.com/
    std::vector<DataT> BreadthFirstSearch(DataT root)
    {
        TraversedList<DataT> discovered;
        InitSearch(discovered);
        return BreadthFirstSearch(root, discovered);
    }

    //! \fn     ConnectedComponents
    ComponentList<DataT> ConnectedComponents()
    {
        TraversedList<DataT> discovered;
        InitSearch(discovered);

        auto component_num = 0;
        ComponentList<DataT> components;

        std::vector<DataT> vertices = GetVertexList();
        for (auto vert : vertices) {
            if (discovered.at(vert) == e_undiscovered) {
                ++component_num;
                std::vector<DataT> bfs = BreadthFirstSearch(vert, discovered);
                components.insert(std::make_pair(component_num, bfs));
            }
        }

        return components;
    }

    //! \fn     DepthFirstSearch
    std::vector<DataT> DepthFirstSearch(DataT root)
    {
        TraversedList<DataT> discovered;
        InitSearch(discovered);
        int time = 0;
        std::vector<DataT> dfs;
        EntryList<DataT> timeclock;
        DoDepthFirstSearch(root, discovered, dfs, time, timeclock);

        return dfs;
    }

    //! \fn     FindPath
    void FindPath(DataT start, DataT end, std::stack<DataT>& path)
    {
        auto pend = m_parents.find(end);
        if ((start == end) || (pend == m_parents.end())) {
            path.push(start);
        } else {
            path.push(end);
            FindPath(start, m_parents.at(end), path);
        }
    }

    //! \fn     GetAdjacencyList
    std::vector<DataT> GetAdjacencyList(DataT vertex) const
    {
        auto edgeit = m_edges.find(vertex);
        if (edgeit != m_edges.end()) {
            std::vector<DataT> adjacencies;

            AdjacencyList<DataT> adjlist = m_edges.at(vertex);
            for (auto adj : adjlist) {
                adjacencies.push_back(adj.dest);
            }

            return adjacencies;
        } else {
            return std::vector<DataT>();
        }
    }

    //! \fn     GetNumEdges
    int GetNumEdges() const
    {
        return m_num_edges;
    }

    //! \fn     GetNumVerts
    int GetNumVerts() const
    {
        return m_num_vertices;
    }

    //! \fn     GetParents
    ParentList<DataT> GetParents() const
    {
        return m_parents;
    }

    //! \fn     GetVertexList
    std::vector<DataT> GetVertexList() const
    {
        std::vector<DataT> verts;
        for (auto edge : m_edges) {
            verts.push_back(edge.first);
        }

        return verts;
    }

    //! \fn     IsDirected
    bool IsDirected() const
    {
        return m_is_directed;
    }

    //! \fn     IsEmpty
    bool IsEmpty() const
    {
        return (m_num_vertices == 0);
    }

    //! \fn     PrintGraph
    void PrintGraph() const
    {
        std::cout << "Graph   : " << (m_is_directed ? "Directed" : "Undirected") << std::endl;
        std::cout << "Vertices: " << m_num_vertices << std::endl;
        std::cout << "Edges   : " << m_num_edges << std::endl;

        std::vector<DataT> verts = GetVertexList();
        for (auto vert : verts) {
            std::cout << std::setw(8) << vert << ": ";
            std::vector<DataT> adjlist = GetAdjacencyList(vert);
            for (auto adj : adjlist) {
                std::cout << adj << " ";
            }

            std::cout << std::endl;
            std::cout << "Degree  : " << m_degrees.at(vert) << std::endl;
        }
    }

    //! \fn     SetDirected
    void SetDirected(bool is_directed)
    {
        m_is_directed = is_directed;
    }

    //! \fn     SetProcessEdgeFn
    void SetProcessEdgeFn(ProcEdgeFn <DataT> func)
    {
        m_edge_proc = func;
    }

    //! \fn     SetProcessVertexEarly
    void SetProcessVertexEarly(ProcVertexFn<DataT> func)
    {
        m_vertex_early = func;
    }

    //! \fn     SetProcessVertexLate
    void SetProcessVertexLate(ProcVertexFn<DataT> func)
    {
        m_vertex_late = func;
    }

    //! \fn     SetTerminationFlag
    void SetTerminationFlag(bool terminate)
    {
        m_terminate = terminate;
    }

private:
    //! \fn     DoAddEdge
    //! \brief  Adds an edge from src to dst; src is the key, all edges from it reside in its edge list
    void DoAddEdge(DataT src, DataT dst)
    {
        // Add edge from src to dst
        AdjacencyNode<DataT> dstnode(dst);

        auto anedge = m_edges.find(src);
        if (anedge == m_edges.end()) {
            ++m_num_vertices;
            AdjacencyList<DataT> nulist;
            m_edges.insert(std::make_pair(src, nulist));
        }

        auto adegree = m_degrees.find(src);
        if (adegree == m_degrees.end()) {
            int num_degrees = 0;
            m_degrees.insert(std::make_pair(src, num_degrees));
        }

        ++m_degrees[src];
        m_edges[src].push_front(dstnode);
        ++m_num_edges;
    }

    //! \fn     DoDepthFirstSearch
    void DoDepthFirstSearch(DataT root, TraversedList<DataT>& discovered,
        std::vector<DataT>& dfs, int time, EntryList<DataT>& timeclock)
    {
        discovered.at(root) = e_discovered;
        dfs.push_back(root);

        int entry_time = ++time;

        m_vertex_early(*this, root);
        std::vector<DataT> adjlist = GetAdjacencyList(root);
        for (auto vert : adjlist) {
            if (discovered.at(vert) == e_undiscovered) {
                m_parents.insert(std::make_pair(root, vert));
                m_edge_proc(*this, root, vert);
                DoDepthFirstSearch(vert, discovered, dfs, time, timeclock);
            } else if ((discovered.at(vert) != e_processed) || IsDirected()) {
                m_edge_proc(*this, root, vert);

                if (m_terminate) {
                    return;
                }
            }
        }
        m_vertex_late(*this, root);

        int exit_time = ++time;

        timeclock.insert(std::make_pair(root, std::make_pair(entry_time, exit_time)));
        discovered.at(root) = e_processed;
    }


    //! \fn     InitSearch
    void InitSearch(TraversedList<DataT>& discovered)
    {
        m_parents.clear();
        std::vector<DataT> vertices = GetVertexList();
        for (auto vert : vertices) {
            std::pair<DataT, VisitedState> init(vert, e_undiscovered);
            discovered.insert(init);
        }
    }

    int m_num_vertices;
    int m_num_edges;
    bool m_is_directed;
    bool m_terminate;

    ProcVertexFn<DataT> m_vertex_early;
    ProcVertexFn<DataT> m_vertex_late;
    ProcEdgeFn<DataT> m_edge_proc;

    EdgeList<DataT> m_edges;
    DegreeList<DataT> m_degrees;
    ParentList<DataT> m_parents;

};

#endif //GRAPHIS_GRAPHIS_HPP
