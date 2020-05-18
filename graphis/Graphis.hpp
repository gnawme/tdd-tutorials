/*! -------------------------------------------------------------------------*\
|   Adjacency list graph representation
|   \see http://www.geeksforgeeks.org/graph-and-its-representations/
\*---------------------------------------------------------------------------*/
#pragma once

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

/// \struct AdjacencyNode
template<typename DataT>
struct AdjacencyNode {
    ///
    AdjacencyNode(DataT dest) : dest(dest), weight(0) {}

    ///
    AdjacencyNode(DataT dest, int weight) : dest(dest), weight(weight) {}

    bool operator<(const AdjacencyNode<DataT>& lhs) const {
        return dest < lhs.dest;
    }

    DataT dest;
    int weight;
};

/// \enum   VisitedState
enum class VisitedState { VS_UNDISCOVERD, VS_DISCOVERED, VS_PROCESSED };

/// \enum   EdgeClassification
enum class EdgeClassification {
    EC_TREE,
    EC_BACK_EDGE,
    EC_FORWARD_EDGE,
    EC_CROSS_EDGE,
    EC_UNCLASSIFIED
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
using WeightList = std::map<DataT, int>;

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

/// fn      ProcessVertexEarly
template<typename DataT>
void ProcessVertexEarly(Graphis<DataT>& graph, DataT vertex) {}

/// fn      ProcessVertexLate
template<typename DataT>
void ProcessVertexLate(Graphis<DataT>& graph, DataT vertex) {}

///
template<typename DataT>
void ProcessEdge(Graphis<DataT>& graph, DataT v1, DataT v2) {}

/// class   Graphis
template<typename DataT>
class Graphis {
public:
    ///
    Graphis(bool is_directed = false)
            : m_num_vertices(0)
            , m_num_edges(0)
            , m_is_directed(is_directed)
            , m_terminate(false)
            , m_vertex_early(ProcessVertexEarly)
            , m_vertex_late(ProcessVertexLate)
            , m_edge_proc(ProcessEdge) {}

    ///
    Graphis(int num_vertices, bool is_directed)
            : m_num_vertices(num_vertices)
            , m_num_edges(0)
            , m_is_directed(is_directed)
            , m_terminate(false)
            , m_vertex_early(ProcessVertexEarly)
            , m_vertex_late(ProcessVertexLate)
            , m_edge_proc(ProcessEdge) {}

    ///
    void AddEdge(DataT src, DataT dst, int weight = 0) {
        // Add edge from src to dst
        DoAddEdge(src, dst, weight);

        // Add edge from dst to src for undirected graph
        if (!m_is_directed) {
            DoAddEdge(dst, src, weight);
        }
    }

    ///
    /// \see    http://www.geeksforgeeks.org/breadth-first-traversal-for-a-graph/ or
    /// http://www.algorist.com/
    std::vector<DataT> BreadthFirstSearch(DataT root) {
        InitSearch();
        return DoBreadthFirstSearch(root);
    }

    ///
    ComponentList<DataT> ConnectedComponents() {
        InitSearch();

        auto component_num = 0;
        ComponentList<DataT> components;

        std::vector<DataT> vertices = GetVertexList();
        for (auto vert : vertices) {
            if (m_discovered.at(vert) == VS_UNDISCOVERD) {
                ++component_num;
                std::vector<DataT> bfs = BreadthFirstSearch(vert);
                components.insert(std::make_pair(component_num, bfs));
            }
        }

        return components;
    }

    ///
    std::vector<DataT> DepthFirstSearch(DataT root, bool init = true) {
        int time = 0;

        if (init) {
            InitSearch();
        }

        std::vector<DataT> dfs;
        DoDepthFirstSearch(root, dfs, time);

        return dfs;
    }

    ///
    std::vector<DataT> DjikstaShortestPath(DataT root) {
        m_parents.clear();
        std::vector<AdjacencyNode<DataT>> nodes = GetNodeList();
        WeightList<DataT> distances;
        for (auto node : nodes) {
            distances.insert(std::make_pair(node.dest, std::numeric_limits<int>::max()));
        }

        distances.at(root) = 0;

        std::vector<DataT> in_span;
        auto current = root;
        while (std::find(in_span.begin(), in_span.end(), current) == in_span.end()) {
            in_span.push_back(current);
            AdjacencyList<DataT> adjlist = GetAdjacencyList(current);
            for (auto adj : adjlist) {
                auto candidate = adj.dest;
                auto weight = adj.weight;

                auto inc = std::find(in_span.begin(), in_span.end(), candidate);
                if ((distances.at(candidate) > distances.at(current) + weight)
                    && (inc == in_span.end())) {
                    distances.at(candidate) = distances.at(current) + weight;
                    m_parents.insert(std::make_pair(candidate, current));
                }
            }

            auto mindist = std::numeric_limits<int>::max();
            for (auto node : nodes) {
                auto inc = std::find(in_span.begin(), in_span.end(), node.dest);
                if ((inc == in_span.end()) && (mindist > distances.at(node.dest))) {
                    mindist = distances.at(node.dest);
                    current = node.dest;
                }
            }
        }

        return in_span;
    }

    ///
    void FindPath(DataT start, DataT end, std::stack<DataT>& path) {
        auto pend = m_parents.find(end);
        if ((start == end) || (pend == m_parents.end())) {
            path.push(start);
        } else {
            path.push(end);
            FindPath(start, m_parents.at(end), path);
        }
    }

    ///
    AdjacencyList<DataT> GetAdjacencyList(DataT vertex) const {
        auto edgeit = m_edges.find(vertex);
        if (edgeit != m_edges.end()) {
            return m_edges.at(vertex);
        } else {
            return AdjacencyList<DataT>();
        }
    }

    ///
    std::vector<DataT> GetAdjacentVertices(DataT vertex) const {
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

    ///
    EdgeClassification GetEdgeClassification(DataT v1, DataT v2) {
        auto pend = m_parents.find(v2);
        if (pend != m_parents.end()) {
            if (m_parents.at(v2) != v1) {
                return EC_TREE;
            }
        }

        auto visited = m_discovered.at(v2);
        if ((visited == VS_DISCOVERED) && (visited != VS_PROCESSED)) {
            return EC_BACK_EDGE;
        }

        auto tyme1 = m_timeclock.find(v1);
        auto tyme2 = m_timeclock.find(v2);
        if ((tyme1 != m_timeclock.end()) && (tyme2 != m_timeclock.end())) {
            if (visited == VS_PROCESSED) {
                auto t1 = tyme1->second;
                auto t2 = tyme2->second;

                if (t2.first > t1.first) {
                    return EC_FORWARD_EDGE;
                }

                if (t2.first < t1.first) {
                    return EC_CROSS_EDGE;
                }
            }
        }

        return EC_UNCLASSIFIED;
    }

    ///
    std::vector<AdjacencyNode<DataT>> GetNodeList() const {
        std::set<AdjacencyNode<DataT>> nodes;
        for (auto edge : m_edges) {
            for (auto node : edge.second) {
                nodes.insert(node.dest);
            }
        }

        return std::vector<AdjacencyNode<DataT>>(nodes.begin(), nodes.end());
    }

    ///
    int GetNumEdges() const {
        return m_num_edges;
    }

    ///
    int GetNumVerts() const {
        return m_num_vertices;
    }

    ///
    ParentList<DataT> GetParents() const {
        return m_parents;
    }

    ///
    std::vector<DataT> GetVertexList() const {
        std::set<DataT> verts;
        for (auto edge : m_edges) {
            verts.insert(edge.first);
            for (auto node : edge.second) {
                verts.insert(node.dest);
            }
        }

        return std::vector<DataT>(verts.begin(), verts.end());
    }

    ///
    bool IsDirected() const {
        return m_is_directed;
    }

    ///
    bool isEmpty() const {
        return (m_num_vertices == 0);
    }

    ///
    std::vector<DataT> PrimSpanningTree(DataT root) {
        m_parents.clear();
        std::vector<AdjacencyNode<DataT>> nodes = GetNodeList();
        WeightList<DataT> distances;
        for (auto node : nodes) {
            distances.insert(std::make_pair(node.dest, std::numeric_limits<int>::max()));
        }

        distances.at(root) = 0;

        std::vector<DataT> in_span;
        auto current = root;
        while (std::find(in_span.begin(), in_span.end(), current) == in_span.end()) {
            in_span.push_back(current);
            AdjacencyList<DataT> adjlist = GetAdjacencyList(current);
            for (auto adj : adjlist) {
                auto candidate = adj.dest;
                auto weight = adj.weight;

                auto inc = std::find(in_span.begin(), in_span.end(), candidate);
                if ((distances.at(candidate) > weight) && (inc == in_span.end())) {
                    distances.at(candidate) = weight;
                    m_parents.insert(std::make_pair(candidate, current));
                }
            }

            auto mindist = std::numeric_limits<int>::max();
            for (auto node : nodes) {
                auto inc = std::find(in_span.begin(), in_span.end(), node.dest);
                if ((inc == in_span.end()) && (mindist > distances.at(node.dest))) {
                    mindist = distances.at(node.dest);
                    current = node.dest;
                }
            }
        }

        return in_span;
    }

    ///
    void PrintGraph() const {
        std::cout << "Graph   : " << (m_is_directed ? "Directed" : "Undirected") << std::endl;
        std::cout << "Vertices: " << m_num_vertices << std::endl;
        std::cout << "Edges   : " << m_num_edges << std::endl;

        std::vector<DataT> verts = GetVertexList();
        for (auto vert : verts) {
            std::cout << std::setw(8) << vert << ": ";
            std::vector<DataT> adjlist = GetAdjacentVertices(vert);
            for (auto adj : adjlist) {
                std::cout << adj << " ";
            }

            std::cout << std::endl;

            auto degrees = 0;
            auto adegree = m_degrees.find(vert);
            if (adegree != m_degrees.end()) {
                degrees = m_degrees.at(vert);
            } else {
                degrees = 0;
            }

            std::cout << "Degree  : " << degrees << std::endl;
        }
    }

    ///
    void PushSorted(DataT vertex) {
        m_sorted.push(vertex);
    }

    ///
    void SetDirected(bool is_directed) {
        m_is_directed = is_directed;
    }

    ///
    void SetProcessEdgeFn(ProcEdgeFn<DataT> func) {
        m_edge_proc = func;
    }

    ///
    void SetProcessVertexEarly(ProcVertexFn<DataT> func) {
        m_vertex_early = func;
    }

    ///
    void SetProcessVertexLate(ProcVertexFn<DataT> func) {
        m_vertex_late = func;
    }

    ///
    void SetTerminationFlag(bool terminate) {
        m_terminate = terminate;
    }

    ///
    std::vector<DataT> TopologicalSort() {
        InitSearch();
        ClearSorted();

        std::vector<DataT> dfs;
        std::vector<DataT> vertices = GetVertexList();
        for (auto vertex : vertices) {
            if (m_discovered.at(vertex) == VS_UNDISCOVERD) {
                dfs = DepthFirstSearch(vertex, false);
            }
        }

        std::vector<DataT> sorted;
        while (!m_sorted.empty()) {
            sorted.push_back(m_sorted.top());
            m_sorted.pop();
        }

        return sorted;
    }

private:
    ///
    void ClearSorted() {
        while (!m_sorted.empty()) {
            m_sorted.pop();
        }
    }

    ///
    /// \brief  Adds an edge from src to dst; src is the key, all edges from it reside in its edge
    /// list
    void DoAddEdge(DataT src, DataT dst, int weight = 0) {
        // Add edge from src to dst
        AdjacencyNode<DataT> dstnode(dst, weight);

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

    ///
    std::vector<DataT> DoBreadthFirstSearch(DataT root) {
        std::queue<DataT> kew;
        m_discovered.at(root) = VS_DISCOVERED;
        kew.push(root);

        std::vector<DataT> bfs;
        while (!kew.empty()) {
            DataT current_vertex = kew.front();
            bfs.push_back(current_vertex);
            kew.pop();
            m_discovered.at(current_vertex) = VS_PROCESSED;
            m_vertex_early(*this, current_vertex);

            std::vector<DataT> adjlist = GetAdjacentVertices(current_vertex);
            for (auto vert : adjlist) {
                if ((m_discovered.at(vert) != VS_PROCESSED) || IsDirected()) {
                    m_edge_proc(*this, root, vert);
                }

                if (m_discovered.at(vert) == VS_UNDISCOVERD) {
                    m_discovered.at(vert) = VS_DISCOVERED;
                    kew.push(vert);
                    m_parents.insert(std::make_pair(vert, current_vertex));
                }
            }

            m_vertex_late(*this, current_vertex);
        }

        return bfs;
    }

    ///
    void DoDepthFirstSearch(DataT root, std::vector<DataT>& dfs, int time) {
        m_discovered.at(root) = VS_DISCOVERED;
        dfs.push_back(root);

        int entry_time = ++time;

        m_vertex_early(*this, root);
        std::vector<DataT> adjlist = GetAdjacentVertices(root);
        for (auto vert : adjlist) {
            if (m_discovered.at(vert) == VS_UNDISCOVERD) {
                m_parents.insert(std::make_pair(root, vert));
                m_edge_proc(*this, root, vert);
                DoDepthFirstSearch(vert, dfs, time);
            } else if ((m_discovered.at(vert) != VS_PROCESSED) || IsDirected()) {
                m_edge_proc(*this, root, vert);

                if (m_terminate) {
                    return;
                }
            }
        }
        m_vertex_late(*this, root);

        int exit_time = ++time;

        m_timeclock.insert(std::make_pair(root, std::make_pair(entry_time, exit_time)));
        m_discovered.at(root) = VS_PROCESSED;
    }

    ///
    void InitSearch() {
        m_parents.clear();
        m_discovered.clear();
        m_timeclock.clear();
        std::vector<DataT> vertices = GetVertexList();
        for (auto vert : vertices) {
            std::pair<DataT, VisitedState> init(vert, VS_UNDISCOVERD);
            m_discovered.insert(init);
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
    TraversedList<DataT> m_discovered;
    EntryList<DataT> m_timeclock;
    std::stack<DataT> m_sorted;
};
