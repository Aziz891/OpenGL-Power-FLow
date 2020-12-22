#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graph_traits.hpp>
#include <iostream>
#include <utility>  // for std::pair
#include "model.hpp"

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;

class Power_Graph
{
private:
    /* data */
    Graph _graph; 
    model &_model;
public:
    Power_Graph(model &model);
    ~Power_Graph();
};
