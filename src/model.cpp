#include "model.hpp"

#include <iostream>

model::model(Matrix<pf_rect, Dynamic, Dynamic, RowMajor> admit,
             std::vector<bus> busses, std::vector<line> lines)
    : _n_busses(busses.size()), _admit(admit), _busses(busses), _lines(lines) {
  Matrix<pf_rect, Dynamic, Dynamic, RowMajor> test_admit;
  test_admit.resize(_n_busses, _n_busses);
  std::for_each(lines.begin(), lines.end(), [&test_admit](line &i) {
    test_admit(i._from_bus, i._from_bus) += (std::complex<double>(1, 0) / i._z);
    test_admit(i._from_bus, i._to_bus) = (std::complex<double>(-1, 0) / i._z);
    test_admit(i._to_bus, i._to_bus) += (std::complex<double>(1, 0) / i._z);
    test_admit(i._to_bus, i._from_bus) = (std::complex<double>(-1, 0) / i._z);
  });
  // std::cout << test_admit;
  _n_busses = _n_busses;
}
model::model() {}

model::~model() {}

void model::generate_admit() {
  _n_busses = _busses.size();
  _admit.resize(_n_busses, _n_busses);
  std::for_each(_lines.begin(), _lines.end(), [&](line &i) {
    _admit(i._from_bus, i._from_bus) += (std::complex<double>(1, 0) / i._z) + i._shunt_admit[0];
    _admit(i._from_bus, i._to_bus) += (std::complex<double>(-1, 0) / i._z);
    _admit(i._to_bus, i._to_bus) += (std::complex<double>(1, 0) / i._z) + i._shunt_admit[1];
    _admit(i._to_bus, i._from_bus) += (std::complex<double>(-1, 0) / i._z);
  });
  // std::cout << _admit;
}

double model::calc_p(size_t i) {
  double test = 0;

  for (size_t k = 0; k < _n_busses; k++) {
    test += _busses[i].voltage * _busses[k].voltage * std::abs(_admit(i, k)) *
            (cos(std::arg(_admit(i, k)) - _busses[i].angle + _busses[k].angle));
  }
  return test;
}

double model::calc_q(size_t i) {
  double test = 0;

  for (size_t k = 0; k < _n_busses; k++) {
    test += -1 * _busses[i].voltage * _busses[k].voltage *
            std::abs(_admit(i, k)) *
            (sin(std::arg(_admit(i, k)) - _busses[i].angle + _busses[k].angle));
  }
  return test;
}
