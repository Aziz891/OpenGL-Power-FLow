#include "solver.hpp"

#include <iostream>
#include <vector>

#include "types.hpp"

using namespace Eigen;

solver::solver(model &a)
    : _model(a), _jacobian(jacobian_gen(_model._admit, _model._busses, 5, _model)) {
  deltas.resize(2 * _model._n_busses - 2 - 5);
}

solver::~solver() {}

double solver::calc_p(size_t i) {
  double test = 0;

  for (size_t k = 0; k < _model._n_busses; k++) {
    test += _model._busses[i].voltage * _model._busses[k].voltage *
            std::abs(_model._admit(i, k)) *
            (cos(std::arg(_model._admit(i, k)) - _model._busses[i].angle +
                 _model._busses[k].angle));
  }
  return test;
}

double solver::calc_q(size_t i) {
  double test = 0;

  for (size_t k = 0; k < _model._n_busses; k++) {
    test += -1 * _model._busses[i].voltage * _model._busses[k].voltage *
            std::abs(_model._admit(i, k)) *
            (sin(std::arg(_model._admit(i, k)) - _model._busses[i].angle +
                 _model._busses[k].angle));
  }
  return test;
}

void solver::calculate_deltas() {
  int counter = 0;
  for (size_t i = 1; i < _model._n_busses ; i++) {
    /* code */
    deltas(i) =
        -1 * _model._busses[i]._loads.real() + _model._busses[i]._p - calc_p(i);
    counter++;
  }

  // for (size_t i = 0; i < _model._n_busses - 1 - 5; i++) {
  //   /* code */
  //   deltas(i + _model._n_busses - 1) =
  //       -1 * _model._busses[i + 1]._loads.imag() + _model._busses[i + 1]._q - calc_q(i);
  //   counter++;
  // }

  for (size_t i = 1; i < _model._n_busses ; i++) {
    /* code */
    if(_model._busses[i]._type != bus_type::pv)
    deltas(i ) =
        -1 * _model._busses[i ]._loads.imag() + _model._busses[i ]._q - calc_q(i);
    counter++;
  }

  std::cout << deltas << std::endl;
  std::cout << "===============>>>" << std::endl;
  // std::cout << "";
  // deltas(0) = -4 - (calc_p(1));
  // deltas(1) = 2 - (calc_p(2));
  // deltas(2) = -2.5 - (calc_q(1));
}

void solver::eval_deltas(Eigen::Matrix<double, Dynamic, 1> &sol) {
  int counter = 0;
  for (size_t i = 0; i < _model._n_busses - 1; i++) {
    /* code */
    _model._busses[i + 1].angle += sol(i);
    counter++;
  }

  for (size_t i = 0; i < _model._n_busses - 1 - 5; i++) {
    /* code */
    _model._busses[i + 1].voltage += sol(i + _model._n_busses - 1);
    counter++;
  }

  // std::cout << deltas << std::endl;
  // std::cout << "";
  // deltas(0) = -4 - (calc_p(1));
  // deltas(1) = 2 - (calc_p(2));
  // deltas(2) = -2.5 - (calc_q(1));
}

void solver::solve() {
  for (size_t i = 0; i < 3; i++) {
    calculate_deltas();
    auto mat = _jacobian.get_jacobian();
    _jacobian.print_jacobians();
    // std::cout << mat;

    Eigen::Matrix<double, Dynamic, 1> sol =
        mat.colPivHouseholderQr().solve(deltas);
    eval_deltas(sol);

    // std::cout << sol << std::endl ;
  }

  std::for_each(_model._busses.begin(), _model._busses.end(), [](bus &i) {
    std::cout << i.voltage << "< " << i.angle * (180 / M_PI) << std::endl;
  });
}
