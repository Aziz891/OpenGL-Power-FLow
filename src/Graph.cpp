#include "Graph.hpp"

#include "model.hpp"

Power_Graph::Power_Graph(model &model) : _model(model) {

  std::vector<int> seen_lines;

  std::for_each(_model._busses.begin(), _model._busses.end() , [&](bus &i) {
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

}

Power_Graph::~Power_Graph() {}

