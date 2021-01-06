#ifndef GRAPH_HG
#define GRAPH_HG

#include <iostream>
#include <utility>  // for std::pair
#include <map>  // for std::pair

#include "model.hpp"

typedef std::map<int, std::vector<int>> l_order;
class Power_Graph {
 private:
  /* data */
  model &_model;
  l_order line_order;

 public:
  Power_Graph(model &model);
  l_order& get_line_order() { return line_order; };
  ~Power_Graph();
};

;

#endif