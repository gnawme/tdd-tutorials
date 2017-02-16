/*! -------------------------------------------------------------------------*\
|   Adjacency list graph representation
|   \see http://www.geeksforgeeks.org/graph-and-its-representations/
\*---------------------------------------------------------------------------*/
#ifndef GRAPHIS_GRAPHIS_HPP
#define GRAPHIS_GRAPHIS_HPP

#include <iostream>
#include <list>
#include <map>
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
using AdjacencyList = std::list<AdjacencyNode<DataT>>;

template<typename DataT>
using EdgeList = std::map<DataT, AdjacencyList<DataT>>;

template<typename DataT>
using DegreeList = std::map<DataT, int>;

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
    {}

    //! \fn     Graphis::Graphis
    Graphis(int num_vertices, bool is_directed)
    : m_num_vertices(num_vertices)
    , m_num_edges(0)
    , m_is_directed(is_directed)
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

    //! \fn     GetVertexList
    std::vector<DataT> GetVertexList() const
    {
        std::vector<DataT> verts;
        for (auto edge : m_edges) {
            verts.push_back(edge.first);
        }

        return verts;
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

    int m_num_vertices;
    int m_num_edges;
    bool m_is_directed;
    EdgeList<DataT> m_edges;
    DegreeList<DataT> m_degrees;
};

#endif //GRAPHIS_GRAPHIS_HPP
