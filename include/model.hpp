#ifndef MODEL_HG
#define MODEL_HG

#include <complex>
#include <eigen3/Eigen/Dense>
#include <vector>

#include "bus.hpp"
#include "line.hpp"
typedef std::complex<double> pf_rect;
// using namespace Eigen;

class model {
 private:
  /* data */

 public:
  size_t _n_busses;
  std::vector<bus> _busses;
  std::vector<line> _lines;
  Eigen::Matrix<pf_rect, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> _admit;
  model(std::vector<bus> busses, std::vector<line> lines);
  model();
  void generate_admit();
  ~model();
  double calc_p(size_t i);
  double calc_q(size_t i);
};

#endif