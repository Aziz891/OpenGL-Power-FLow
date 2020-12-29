#include "Graph.hpp"

#include "model.hpp"

Power_Graph::Power_Graph(model &model) : _model(model) {
  // Make convenient labels for the vertices
  //   enum { A, B, C, D, E, N };
  // const int num_vertices = _model._n_busses;
  // //   const char* name = "ABCDE";

  // // writing out the edges in the graph
  // typedef std::pair<int, int> Edge;
  // //   Edge edge_array[] = {Edge(A, B), Edge(A, D), Edge(C, A), Edge(D, C),
  // //                        Edge(C, E), Edge(B, D), Edge(D, E)};
  // //   const int num_edges = sizeof(edge_array) / sizeof(edge_array[0]);

  // // declare a graph object
  // _graph = Graph (num_vertices);

  // // add the edges to the graph object
  // //   for (int i = 0; i < num_edges; ++i)
  // // add_edge(edge_array[i].first, edge_array[i].second, g);
  // std::for_each(_model._lines.begin(), _model._lines.end(), [&](line &i) {
  //   boost::add_edge(i._from_bus, i._to_bus, _graph);
  // });

  // std::vector<int> test{0,1};
  std::vector<int> seen_lines;

  std::for_each(_model._busses.begin(), _model._busses.end() , [&](bus &i) {
    // line_order[i._number] = std::vector<std::vector<int>>();
    auto pred_line = [&](line &j) {
      return ((j._from_bus +1  == i._number || j._to_bus +1 == i._number) &&
              (std::find(seen_lines.begin(), seen_lines.end(),j._number ) ==
               seen_lines.end()));
    };
    auto it =
        std::find_if(_model._lines.begin(), _model._lines.end(), pred_line);
    line_order[i._number] = std::vector<int>();
    while (it != _model._lines.end()) {
      line_order[i._number].push_back(it - _model._lines.begin());
      seen_lines.push_back(it->_number);
      it = std::find_if(++it, _model._lines.end(), pred_line);
    }
  });

  // my_visitor vis(line_order);
  // breadth_first_search(_graph, 0, boost::visitor(vis));
  std::cout << "";
}

Power_Graph::~Power_Graph() {}

//   using namespace boost;
//   // Select the graph type we wish to use
//   typedef adjacency_list < vecS, vecS, undirectedS > graph_t;
//   // Set up the vertex IDs and names
//   enum { r, s, t, u, v, w, x, y, N };
//   const char *name = "rstuvwxy";
//   // Specify the edges in the graph
//   typedef std::pair < int, int >E;
//   E edge_array[] = { E(r, s), E(r, v), E(s, w), E(w, r), E(w, t),
//     E(w, x), E(x, t), E(t, u), E(x, y), E(u, y)
//   };
//   // Create the graph object
//   const int n_edges = sizeof(edge_array) / sizeof(E);
// #if defined(BOOST_MSVC) && BOOST_MSVC <= 1300
//   // VC++ has trouble with the edge iterator constructor
//   graph_t g(N);
//   for (std::size_t j = 0; j < n_edges; ++j)
//     add_edge(edge_array[j].first, edge_array[j].second, g);
// #else
//   typedef graph_traits<graph_t>::vertices_size_type v_size_t;
//   graph_t g(edge_array, edge_array + n_edges, v_size_t(N));
// #endif

//   // Typedefs
//   typedef graph_traits < graph_t >::vertex_descriptor Vertex;
//   typedef graph_traits < graph_t >::vertices_size_type Size;
//   typedef Size* Iiter;

//   // a vector to hold the discover time property for each vertex
//   std::vector < Size > dtime(num_vertices(g));

//   Size time = 0;
//   bfs_time_visitor < Size * >vis(&dtime[0], time);
//   breadth_first_search(g, vertex(s, g), visitor(vis));

//   // Use std::sort to order the vertices by their discover time
//   std::vector<graph_traits<graph_t>::vertices_size_type > discover_order(N);
//   integer_range < int >range(0, N);
//   std::copy(range.begin(), range.end(), discover_order.begin());
//   std::sort(discover_order.begin(), discover_order.end(),
//             indirect_cmp < Iiter, std::less < Size > >(&dtime[0]));

//   std::cout << "order of discovery: ";
//   for (int i = 0; i < N; ++i)
//     std::cout << name[discover_order[i]] << " ";
//   std::cout << std::endl;

//   template < typename TimeMap > class bfs_time_visitor:public
//   default_bfs_visitor { typedef typename property_traits < TimeMap
//   >::value_type T;
// public:
//   bfs_time_visitor(TimeMap tmap, T & t):m_timemap(tmap), m_time(t) { }
//   template < typename Vertex, typename Graph >
//     void discover_vertex(Vertex u, const Graph & g) const
//   {
//     put(m_timemap, u, m_time++);
//   }
//   TimeMap m_timemap;
//   T & m_time;
// };