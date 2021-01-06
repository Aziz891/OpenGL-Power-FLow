#ifndef RENDER_HG
#define RENDER_HG
#include "Graph.hpp"
#include "mesh.h"
#include "model.hpp"
#include <memory>
class Renderer {
 private:
  /* data */
  l_order& line_order;
  model& _model;

 public:
  Renderer(l_order &lines,model &model);
  ~Renderer();
  std::vector<std::unique_ptr<Mesh>> render();
};

#endif