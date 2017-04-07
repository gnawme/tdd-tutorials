#include "Graphis.hpp"

#include <gmock/gmock.h>
#include <vector>

//! \class  GraphisTest
class GraphisTest: public ::testing::Test
{
public:
    virtual void SetUp()
    {}

    void LoadADM()
    {
        adm.AddEdge('A', 'B', 5);
        adm.AddEdge('B', 'C', 7);
        adm.AddEdge('B', 'D', 9);
        adm.AddEdge('A', 'D', 7);
        adm.AddEdge('A', 'E', 12);
        adm.AddEdge('C', 'D', 4);
        adm.AddEdge('D', 'E', 4);
        adm.AddEdge('E', 'F', 7);
        adm.AddEdge('D', 'F', 3);
        adm.AddEdge('C', 'F', 2);
        adm.AddEdge('F', 'G', 2);
        adm.AddEdge('C', 'G', 5);
    }

    void LoadDAG()
    {
        dag.SetDirected(true);
        dag.AddEdge('A', 'C');
        dag.AddEdge('A', 'B');
        dag.AddEdge('B', 'C');
        dag.AddEdge('B', 'D');
        dag.AddEdge('C', 'E');
        dag.AddEdge('E', 'D');
        dag.AddEdge('C', 'F');
        dag.AddEdge('F', 'E');
        dag.AddEdge('G', 'F');
        dag.AddEdge('G', 'A');
    }

    void LoadGeekGraph()
    {
        graph1.AddEdge(0, 1);
        graph1.AddEdge(0, 4);
        graph1.AddEdge(1, 2);
        graph1.AddEdge(1, 3);
        graph1.AddEdge(1, 4);
        graph1.AddEdge(2, 3);
        graph1.AddEdge(3, 4);
    }

    void LoadSearchGraph()
    {
        graph2.SetDirected(true);
        graph2.AddEdge(0, 1);
        graph2.AddEdge(0, 2);
        graph2.AddEdge(1, 2);
        graph2.AddEdge(2, 0);
        graph2.AddEdge(2, 3);
        graph2.AddEdge(3, 3);
    }

    void LoadRouteGraph()
    {
        allegiant.AddEdge("LAX", "BLI", 1047);
        allegiant.AddEdge("LAX", "BOI", 674);
        allegiant.AddEdge("LAX", "EUG", 748);
        allegiant.AddEdge("LAX", "IDA", 743);
        allegiant.AddEdge("LAX", "MFR", 630);
        allegiant.AddEdge("LAX", "PSC", 851);
        allegiant.AddEdge("LAX", "RNO", 390);
        allegiant.AddEdge("OAK", "BLI", 764);
        allegiant.AddEdge("OAK", "EUG", 445);
        allegiant.AddEdge("OAK", "IDA", 666);
        allegiant.AddEdge("OAK", "LAS", 407);
        allegiant.AddEdge("OAK", "AZA", 668);
        allegiant.AddEdge("AZA", "BLI", 1208);
        allegiant.AddEdge("AZA", "EUG", 971);
        allegiant.AddEdge("AZA", "FAT", 516);
        allegiant.AddEdge("AZA", "IDA", 704);
        allegiant.AddEdge("AZA", "MFR", 875);
        allegiant.AddEdge("AZA", "LAS", 276);
        allegiant.AddEdge("AZA", "OAK", 668);
        allegiant.AddEdge("AZA", "PSC", 977);
        allegiant.AddEdge("AZA", "STS", 721);
        allegiant.AddEdge("AZA", "SCK", 625);
    }

    Graphis<int> graph1;
    Graphis<int> graph2;
    Graphis<std::string> allegiant;
    Graphis<char> dag;
    Graphis<char> adm;
};

//! \test   EmptyGraphShouldReturnEmpty
TEST_F(GraphisTest, EmptyGraphShouldReturnEmpty) {

    EXPECT_TRUE(graph1.IsEmpty());
}

//! \test   AddingFiveVerticesShouldReturnSizeFive
TEST_F(GraphisTest, AddingFiveVerticesShouldReturnSizeFive) {
    LoadGeekGraph();
    EXPECT_EQ(graph1.GetNumVerts(), 5);
}

//! \test   VertexListShouldMatchExpectedSize
TEST_F(GraphisTest, VertexListShouldMatchExpectedSize) {
    LoadGeekGraph();

    std::vector<int> verts = graph1.GetVertexList();
    EXPECT_EQ(verts.size(), graph1.GetNumVerts());
}

//! \test   NumberOfEdgesShouldEqualFourteen
TEST_F(GraphisTest, NumberOfEdgesShouldEqualFourteen) {
    LoadGeekGraph();
    EXPECT_THAT(14, graph1.GetNumEdges());
}

//! \test   AdjacencyListsShouldMatchExpected
TEST_F(GraphisTest, AdjacencyListsShouldMatchExpected) {
    LoadGeekGraph();

    std::vector<int> v0list{4, 1};
    std::vector<int> v1list{4, 3, 2, 0};
    std::vector<int> v2list{3, 1};

    std::vector<int> v0adj = graph1.GetAdjacentVertices(0);
    EXPECT_THAT(v0list, ::testing::Eq(v0adj));
    std::vector<int> v1adj = graph1.GetAdjacentVertices(1);
    EXPECT_THAT(v1list, ::testing::Eq(v1adj));
    std::vector<int> v2adj = graph1.GetAdjacentVertices(2);
    EXPECT_THAT(v2list, ::testing::Eq(v2adj));
}

//! \test   BreadthFirstSearchShouldMatchExpected
TEST_F(GraphisTest, BreadthFirstSearchShouldMatchExpected) {
    LoadSearchGraph();

    std::vector<int> v1bfs{1, 2, 3, 0};
    std::vector<int> v1reach = graph2.BreadthFirstSearch(1);
    EXPECT_THAT(v1bfs, ::testing::Eq(v1reach));

    std::vector<int> v3bfs{3};
    std::vector<int> v3reach = graph2.BreadthFirstSearch(1);
    EXPECT_THAT(v3bfs, ::testing::Eq(v3bfs));
}

//! \test   FindPathShouldReturnExpected {
TEST_F(GraphisTest, FindPathShouldReturnExpected) {
    LoadRouteGraph();
    // Must perform BFS from start node to get meaningful results
    std::vector<std::string> bfsout = allegiant.BreadthFirstSearch("LAX");

    std::vector<std::string> route{"LAX", "PSC", "AZA", "LAS"};
    std::stack<std::string> path;
    allegiant.FindPath("LAX", "LAS", path);

    std::vector<std::string> laxroute;
    while (!path.empty()) {
        laxroute.push_back(path.top());
        path.pop();
    }

    EXPECT_THAT(route, ::testing::Eq(laxroute));
}

//! \test   ConnectedComponentsShouldReturnExpected
TEST_F(GraphisTest, ConnectedComponentsShouldReturnExpected) {
    LoadRouteGraph();

    ComponentList<std::string> connected = allegiant.ConnectedComponents();

    EXPECT_EQ(1, connected.size());

    std::vector<std::string> conset{
        "AZA", "SCK", "STS", "PSC", "OAK", "LAS", "MFR", "IDA", "FAT", "EUG", "BLI", "LAX", "RNO", "BOI"
    };

    std::vector<std::string> inset;
    for (auto component : connected) {
        for (auto conlist : component.second) {
            inset.push_back(conlist);
        }
    }

    EXPECT_THAT(conset, ::testing::Eq(inset));
}

//! \test   DepthFirstSearchShouldMatchExpected
TEST_F(GraphisTest, DepthFirstSearchShouldMatchExpected) {
    LoadSearchGraph();

    std::vector<int> dfsout = graph2.DepthFirstSearch(2);
    std::vector<int> expected{2, 3, 0, 1};
    EXPECT_THAT(expected, ::testing::Eq(dfsout));
}

//! \fn     ProcessCycle
template<typename DataT>
void ProcessCycle(Graphis<DataT>& graph, DataT v1, DataT v2)
{
    std::stack<DataT> path;
    graph.FindPath(v2, v1, path);
    graph.SetTerminationFlag(true);

    std::cout << "Cycle found between " << v1 << " and " << v2 << std::endl;
    while (!path.empty()) {
        std::cout << path.top() << " ";
        path.pop();
    }
    std::cout << std::endl;
}

//! \fn     FindCycle
//! \brief  Implements ProcEdgeFn for Depth First Search when finding cycles
template<typename DataT>
void FindCycle(Graphis<DataT>& graph, DataT v1, DataT v2) {
    if (v1 == v2) {
        ProcessCycle(graph, v1, v2);
    }

    ParentList<DataT> parents = graph.GetParents();
    auto parent_of = parents.find(v1);

    if (parent_of != parents.end()) {
        if (parents.at(v1) != v2) {
            ProcessCycle(graph, v1, v2);
        }
    }
}

//! \test   FindingCycleInDFSShouldMatchExpected
TEST_F(GraphisTest, FindingCycleInDFSShouldMatchExpected) {
    LoadSearchGraph();

    graph2.SetProcessEdgeFn(FindCycle);
    std::vector<int> verts = graph2.GetVertexList();
    for (auto vert : verts) {
        std::vector<int> dfsout = graph2.DepthFirstSearch(vert);
    }
}

//! \fn     ClassifyEdges
//! \brief  Implements ProcEdgeFn for Depth First Search when performing topo sort
template<typename DataT>
void ClassifyEdges(Graphis<DataT>& graph, DataT v1, DataT v2)
{
    EdgeClassification eclass = graph.GetEdgeClassification(v1, v2);

    if (eclass == e_back_edge) {
        std::cerr << "WARNING: Directed cycle found, not a DAG" << std::endl;
    }
}

//! \fn     PushSorted
//! \brief  Implements SetProcessVertexLate for DFS when performing topo sort
template<typename DataT>
void PushSorted(Graphis<DataT>& graph, DataT vertex)
{
    graph.PushSorted(vertex);
}

//! \test   TopoSortShouldMatchExpectedTopology
TEST_F(GraphisTest, TopoSortShouldMatchExpectedTopology) {
    LoadDAG();
    std::vector<char> expected{
        'G', 'A', 'B', 'C', 'F', 'E', 'D'
    };

    dag.SetProcessEdgeFn(ClassifyEdges);
    dag.SetProcessVertexLate(PushSorted);
    std::vector<char> sorted = dag.TopologicalSort();
    EXPECT_THAT(expected, ::testing::Eq(sorted));
}

//! \test   PrimSpanningTreeShouldYieldMinimum
TEST_F(GraphisTest, PrimSpanningTreeShouldYieldMinimum) {
    LoadADM();
    std::vector<char> expected{
        'A', 'B', 'C', 'F', 'G', 'D', 'E'
    };

    std::vector<char> span = adm.PrimSpanningTree('A');
    EXPECT_THAT(expected, ::testing::Eq(span));
}

//! \test   DjikstraShortestPathShouldYieldShortest
TEST_F(GraphisTest, DjikstraShortestPathShouldYieldShortest) {
    LoadADM();
    std::vector<char> expected{
        'A', 'B', 'D', 'F', 'C', 'E', 'G'
    };

    std::vector<char> span = adm.DjikstaShortestPath('A');
    EXPECT_THAT(expected, ::testing::Eq(span));
}

//! \fn     main
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}