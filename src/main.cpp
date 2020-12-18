#include <eigen3/Eigen/Dense>
#include <algorithm>
#include <complex>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
// #include <>

#include "jacobian_gen.hpp"
#include "model.hpp"
#include "solver.hpp"
#include "Parser.hpp"

#define N_BUSES 3

using namespace std;
using namespace Eigen;
typedef std::complex<double> pf_rect;


int main(int argc, char const *argv[]) {

  model test_model;
  Parser parser(test_model);
  parser.read();
  test_model.generate_admit();

  // std::vector<bus> busses(N_BUSES, bus(1, 0));
  // std::vector<line> lines;
  // lines.push_back(line(0, 2, std::complex<double>(0.01, 0.03)));
  // lines.push_back(line(0, 1, std::complex<double>(0.02, 0.04)));
  // lines.push_back(line(2, 1, std::complex<double>(0.0125, 0.025)));
  // busses[0].voltage = 1.05;
  // busses[2].voltage = 1.04;
  // Matrix<pf_rect, N_BUSES, N_BUSES, RowMajor> x;
  // Matrix<pf_rect, N_BUSES, N_BUSES, RowMajor> j;
  // x << pf_rect(20, -50), pf_rect(-10, 20), pf_rect(-10, 30), pf_rect(-10, 20),
  //     pf_rect(26, -52), pf_rect(-16, 32), pf_rect(-10, 30), pf_rect(-16, 32),
  //     pf_rect(26, -62);
  // model a{x, busses, lines};
  solver a_solver{test_model};
  a_solver.solve();
  std::cout << " ";
  
  // jacobian_gen x_jacobian(x, busses, 1);

  // for (size_t i = 0; i < 3; i++) {
  //   auto mat = x_jacobian.get_jacobian();
    
  //   Vector3d sol = mat.colPivHouseholderQr().solve(deltas);
  //   busses[1].angle += sol(0);
  //   busses[2].angle += sol(1);
  //   busses[1].voltage += sol(2);
  //   // std::cout << sol << std::endl ;
  // }

  // std::for_each(busses.begin(), busses.end(), [](bus &i) {
  //   std::cout << i.voltage << "< " << i.angle * (180 / M_PI) << std::endl;
  // });

  // MatrixXd A =   MatrixXd::Random(30, 30);
  // VectorXd b = VectorXd::Random(30) ;

  // cout << "Here is the matrix A:\n"
  //      << A << endl;
  // cout << "Here is the vector b:\n"
  //      << b << endl;
  // VectorXd x = A.colPivHouseholderQr().solve(b);
  // cout << "The solution is:\n"
  //      << x << endl;
}
