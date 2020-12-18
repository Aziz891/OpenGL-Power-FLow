#include "jacobian_gen.hpp"

#include <cmath>
#include <iostream>


jacobian_gen::jacobian_gen(Matrix<pf_rect, Dynamic, Dynamic, RowMajor> &admit,
                           std::vector<bus> &busses, size_t n_pv_busses,
                           model &model)
    : _admit(admit),
      _busses(busses),
      _n_pv_busses(n_pv_busses),
      _n_busses(busses.size()),
      _model(model) {
  _jacobian.resize(2 * _n_busses - 2 - _n_pv_busses,
                   2 * _n_busses - 2 - _n_pv_busses);
}

jacobian_gen::~jacobian_gen() {}

void jacobian_gen::calculate_j1() {
  for (size_t i = 1; i < _n_busses; i++) {
    for (size_t j = 1; j < _n_busses; j++) {
      double test = 0;
      if (j == i) {
        for (size_t k = 0; k < _n_busses; k++) {
          if (k == i) continue;
          test += _busses[i].voltage * _busses[k].voltage *
                  std::abs(_admit(i, k)) *
                  (sin(std::arg(_admit(i, k)) - _busses[i].angle +
                       _busses[k].angle));
        }
      } else {
        test =
            -1 * _busses[i].voltage * _busses[j].voltage *
            std::abs(_admit(i, j)) *
            (sin(std::arg(_admit(i, j)) - _busses[i].angle + _busses[j].angle));
      }
      _jacobian(i - 1, j - 1) = test;
      test_test++;
    }
  }
}

void jacobian_gen::calculate_j2() {
  size_t pv_seen = 0;
    for (size_t i = 1; i < _n_busses; i++) {
      pv_seen =0;
    for (size_t j = 1; j < _n_busses; j++) {
      if (_model._busses[j]._type == bus_type::pv)
      {
        pv_seen++;
        continue;
        }
       double test = 0;
      if (j == i) {
        for (size_t k = 0; k < _n_busses; k++) {
          if (k == i) continue;
          test += _busses[k].voltage * std::abs(_admit(i, k)) *
                  (cos(std::arg(_admit(i, k)) - _busses[i].angle +
                       _busses[k].angle));
        }
        test += 2 * _busses[i].voltage * std::abs(_admit(i, i)) *
                cos(std::arg(_admit(i, i)));
      } else {
        test =
            _busses[i].voltage * _busses[j].voltage * std::abs(_admit(i, j)) *
            (cos(std::arg(_admit(i, j)) - _busses[i].angle + _busses[j].angle));
      }
      _jacobian(i - 1, _n_busses - _n_pv_busses + (j - pv_seen - 1)) = test;
      test_test++;
    }
  }
}

void jacobian_gen::calculate_j3() {
  size_t pv_seen = 0;
  for (size_t i = 1; i < _n_busses; i++) {
      if (_model._busses[i]._type == bus_type::pv)
      {pv_seen++; continue;}
    for (size_t j = 1; j < _n_busses; j++) {
      double test = 0;
      if (j == i) {
        for (size_t k = 0; k < _n_busses; k++) {
          if (k == i) continue;
          test += _busses[i].voltage * _busses[k].voltage *
                  std::abs(_admit(i, k)) *
                  (cos(std::arg(_admit(i, k)) - _busses[i].angle +
                       _busses[k].angle));
        }
      } else {
        test =
            -1 * _busses[i].voltage * _busses[j].voltage *
            std::abs(_admit(i, j)) *
            (cos(std::arg(_admit(i, j)) - _busses[i].angle + _busses[j].angle));
      }
      _jacobian(_n_busses - _n_pv_busses + (i - pv_seen - 1), (j - 1)) = test;
      test_test++;
    }
  }
}

void jacobian_gen::calculate_j4() {
    size_t pv_seen = 0;
  for (size_t i = 1; i < _n_busses ; i++) {
    size_t pv_seen2 = 0;
      if (_model._busses[i]._type == bus_type::pv)
      {pv_seen++; continue;}
    for (size_t j = 1; j < _n_busses ; j++) {
      if (_model._busses[j]._type == bus_type::pv)
      {pv_seen2++; continue;}
      double test = 0;
      if (j == i) {
        for (size_t k = 0; k < _n_busses; k++) {
          if (k == i) continue;
          test += _busses[k].voltage * std::abs(_admit(i, k)) *
                  (sin(std::arg(_admit(i, k)) - _busses[i].angle +
                       _busses[k].angle));
        }
        test = -2 * _busses[i].voltage * std::abs(_admit(i, i)) *
                   sin(std::arg(_admit(i, i))) -
               test;
      } else {
        test =
            -1 * _busses[i].voltage * _busses[j].voltage *
            std::abs(_admit(i, j)) *
            (sin(std::arg(_admit(i, j)) - _busses[i].angle + _busses[j].angle));
      }
      _jacobian(_n_busses - _n_pv_busses + (i -pv_seen - 1),
                _n_busses - _n_pv_busses + (j - pv_seen2 - 1)) = test;
                test_test++;
    }
  }
}
Matrix<double, Dynamic, Dynamic, RowMajor> jacobian_gen::get_jacobian() {
  calculate_j1();
  calculate_j2();
  calculate_j3();
  calculate_j4();
  return _jacobian;
}

void jacobian_gen::print_jacobians() {
  std::cout << _jacobian << std::endl;
  std::cout << "================" << std::endl;
}