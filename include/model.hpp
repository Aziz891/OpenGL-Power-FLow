#ifndef MODEL_HG
#define MODEL_HG

#include <eigen3/Eigen/Dense>
#include <complex>
#include <vector>

#include "bus.hpp"
#include "line.hpp"
typedef std::complex<double> pf_rect;
using namespace Eigen;

class model {
 private:
  /* data */

 public:
  size_t _n_busses;
  std::vector<bus> _busses;
  std::vector<line> _lines;
  Matrix<pf_rect, Dynamic, Dynamic, RowMajor> _admit;
  model(Matrix<pf_rect, Dynamic, Dynamic, RowMajor> admit,
        std::vector<bus> busses, std::vector<line> lines);
  model();    
  void generate_admit();
  ~model();
  double calc_p(size_t i);
  double calc_q(size_t i);
};


#endif