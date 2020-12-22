#include "Graph.hpp"
#include "model.hpp"


Power_Graph::Power_Graph(model &model): _model(model)
{
      // Make convenient labels for the vertices
//   enum { A, B, C, D, E, N };
  const int num_vertices = _model._n_busses;
//   const char* name = "ABCDE";

  // writing out the edges in the graph
  typedef std::pair<int, int> Edge;
//   Edge edge_array[] = {Edge(A, B), Edge(A, D), Edge(C, A), Edge(D, C),
//                        Edge(C, E), Edge(B, D), Edge(D, E)};
//   const int num_edges = sizeof(edge_array) / sizeof(edge_array[0]);

  // declare a graph object
  Graph g(num_vertices);

  // add the edges to the graph object
//   for (int i = 0; i < num_edges; ++i)
    // add_edge(edge_array[i].first, edge_array[i].second, g);
std::for_each(_model._lines.begin(), _model._lines.end(), [&](line &i){

    boost::add_edge(i._from_bus, i._to_bus, _graph );



} );

std::cout << "";
}

Power_Graph::~Power_Graph()
{
}
