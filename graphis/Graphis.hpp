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

template<typename DataT>
using AdjacencyList = std::list<AdjacencyNode<DataT>>;

template<typename DataT>
using EdgeList = std::map<DataT, AdjacencyList<DataT>>;

//! class   Graphis
template<typename DataT>
class Graphis
{
public:
    //! \fn     Graphis::Graphis
    Graphis(bool is_directed = false)
    : m_num_vertices(0)
    , m_is_directed(is_directed)
    {}

    //! \fn     Graphis::Graphis
    Graphis(int num_vertices, bool is_directed)
    : m_num_vertices(num_vertices)
    , m_is_directed(is_directed)
    {}

    //! \fn     AddEdge
    void AddEdge(DataT src, DataT dst)
    {
        // Add edge from src to dst
        DoAddEdge(src, dst);

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
    void DoAddEdge(DataT src, DataT dst)
    {
        // Add edge from src to dst
        AdjacencyNode<DataT> dstnode(dst);
        auto srcit = m_edges.find(src);
        if (srcit == m_edges.end()) {
            ++m_num_vertices;
            AdjacencyList<DataT> nulist;
            m_edges.insert(std::make_pair(src, nulist));
        }

        m_edges[src].push_front(dstnode);
    }

    int m_num_vertices;
    bool m_is_directed;
    EdgeList<DataT> m_edges;
};

#endif //GRAPHIS_GRAPHIS_HPP
