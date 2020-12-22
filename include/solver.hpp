#include <eigen3/Eigen/Dense>

#include "bus.hpp"
#include "model.hpp"
#include "jacobian_gen.hpp"
#include "types.hpp"

// using namespace Eigen;
class solver {
 private:
  /* data */
  Eigen::Matrix<double, Eigen::Dynamic, 1> deltas;
  model &_model;
  jacobian_gen _jacobian;

 public:
  solver(model &a ) ;
  ~solver();
  void solve();
  void calculate_deltas();
  void calculate_deltas2();
  void eval_deltas(Eigen::Matrix<double, Eigen::Dynamic, 1> & _sol);
  double calc_p(size_t i);
  double calc_q(size_t i);
};

