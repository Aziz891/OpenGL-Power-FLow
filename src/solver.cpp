#include "solver.hpp"

#include <iostream>
#include <vector>

#include "types.hpp"

using namespace Eigen;
#define TEST_PV 5

solver::solver(model &a)
    : _model(a),
      _jacobian(jacobian_gen(_model._admit, _model._busses, TEST_PV, _model)) {
  deltas.resize(2 * _model._n_busses - 2 - TEST_PV);
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
  std::vector<double> mismatch;
  int counter = 0;
  for (size_t i = 1; i < _model._n_busses; i++) {
    /* code */
    auto test =
        -1 * _model._busses[i]._loads.real() + _model._busses[i]._p - calc_p(i);
    deltas(i - 1) = test;
    mismatch.push_back(test);
    counter++;
  }

  size_t pv_seen = 0;
  for (size_t i = 1; i < _model._n_busses; i++) {
    /* code */
    if (_model._busses[i]._type != bus_type::pv) {
      auto test2 = -1 * _model._busses[i]._loads.imag() + _model._busses[i]._q -
                   calc_q(i);
      deltas(i - 1 + _model._n_busses - 1 - pv_seen) = test2;
    } else {
      pv_seen++;
    }
    counter++;
  }
  auto max = std::max_element(mismatch.begin(), mismatch.end());

  std::cout << "===============>>>" << std::endl;
  std::cout << *max << std::endl;
  // std::cout << "";
}
void solver::calculate_deltas2() {
  deltas(0) = -4 - (calc_p(1));
  deltas(1) = 2 - (calc_p(2));
  deltas(2) = 2 - (calc_p(3));
  deltas(3) = -2.5 - (calc_q(1));
  deltas(4) = -2.5 - (calc_q(3));
}

void solver::eval_deltas(Eigen::Matrix<double, Dynamic, 1> &sol) {
  int counter = 0;
  for (size_t i = 1; i < _model._n_busses; i++) {
    /* code */
    _model._busses[i].angle += sol(i - 1);
    counter++;
  }
  size_t pv_seen = 0;
  for (size_t i = 1; i < _model._n_busses; i++) {
    /* code */
    if (_model._busses[i]._type != bus_type::pv) {
      _model._busses[i].voltage += sol(i - 1 + _model._n_busses - 1 - pv_seen);
    } else {
      pv_seen++;
    }
    if (i - 1 + _model._n_busses - 1 - TEST_PV == 52) counter++;
  }

  // std::cout << deltas << std::endl;
  // std::cout << "";
  // deltas(0) = -4 - (calc_p(1));
  // deltas(1) = 2 - (calc_p(2));
  // deltas(2) = -2.TEST_PV - (calc_q(1));
}

void solver::solve() {
  Eigen::Matrix<double, Dynamic, 1> sol;
  for (size_t i = 0; i < 10; i++) {
    calculate_deltas();
    auto mat = _jacobian.get_jacobian();
    // _jacobian.print_jacobians();
    // std::cout << mat;

    // mat.colPivHouseholderQr().solve(deltas);
    sol = mat.fullPivLu().solve(deltas);
    //  double relative_error = (mat *sol - deltas).norm() / deltas.norm(); //
    //  norm() is L2 norm std::cout << "The relative error is:\n" <<
    //  relative_error << std::endl;
    eval_deltas(sol);

    // std::cout << sol << std::endl ;
  }

  std::for_each(_model._lines.begin(), _model._lines.end(), [&](line &i) {
    i.flows.first = 100.0 * _model._busses[i._from_bus].getRect() *
                    std::conj(_model._admit(i._from_bus, i._to_bus) *
                              (_model._busses[i._from_bus].getRect() -
                               _model._busses[i._to_bus].getRect() ));
    i.flows.second = 100.0 *  _model._busses[i._to_bus].getRect() *
                    std::conj(_model._admit(i._to_bus, i._from_bus) *
                              (_model._busses[i._to_bus].getRect() -
                               _model._busses[i._from_bus].getRect() ));
  });
  std::for_each(_model._busses.begin(), _model._busses.end(), [](bus &i) {
    std::cout << i._number << " : " << i.voltage << "< "
              << i.angle * (180 / M_PI) << std::endl;
  });
}
