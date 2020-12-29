#ifndef GRAPH_HG
#define GRAPH_HG

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graph_traits.hpp>
#include <iostream>
#include <utility>  // for std::pair

#include "model.hpp"

typedef std::map<int, std::vector<int>> l_order;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>
    Graph;
class Power_Graph {
 private:
  /* data */
  Graph _graph;
  model &_model;
  l_order line_order;

 public:
  Power_Graph(model &model);
  l_order& get_line_order() { return line_order; };
  ~Power_Graph();
};

class my_visitor : public boost::default_bfs_visitor {
  l_order &_line_order;
  int _current_node;

 public:
  my_visitor(l_order &lines) : _line_order(lines) {}
  void discover_vertex(const Graph::vertex_descriptor &s, const Graph &g) {
    std::cout << "Initialize: " << s << std::endl;
    _current_node = s;
  }

  void tree_edge(const Graph::edge_descriptor &e, const Graph &g) {
    std::cout << "Initialize: " << e << std::endl;
    // std::cout << e.m_target << "," << e.m_source ;
    // _line_order[_current_node].push_back((int)e.m_source,(int) e.m_target);
    // _line_order.push_back(l_order(_current_node,
    // std::vector<std::vector<int>>{e.m_source, e.m_target}));
  }
  // void discover_vertex(const graph_t::vertex_descriptor &s, const graph_t &g)
  // const {
  //   std::cout << "Discover: " << g[s] << std::endl;
  // }
  // void examine_vertex(const graph_t::vertex_descriptor &s, const graph_t &g)
  // const {
  //   std::cout << "Examine vertex: " << g[s] << std::endl;
  // }
  // void examine_edge(const graph_t::edge_descriptor &e, const graph_t &g)
  // const {
  //   std::cout << "Examine edge: " << g[e] << std::endl;
  // }
  // void tree_edge(const graph_t::edge_descriptor &e, const graph_t &g) const {
  //   std::cout << "Tree edge: " << e << std::endl;
  // }
  // void non_tree_edge(const graph_t::edge_descriptor &e, const graph_t &g)
  // const {
  //   std::cout << "Non-Tree edge: " << g[e] << std::endl;
  // }
  // void gray_target(const graph_t::edge_descriptor &e, const graph_t &g) const
  // {
  //   std::cout << "Gray target: " << g[e] << std::endl;
  // }
  // void black_target(const graph_t::edge_descriptor &e, const graph_t &g)
  // const {
  //   std::cout << "Black target: " << g[e] << std::endl;
  // }
  // void finish_vertex(const graph_t::vertex_descriptor &s, const graph_t &g)
  // const {
  //   std::cout << "Finish vertex: " << g[s] << std::endl;
  // }
};

#endif