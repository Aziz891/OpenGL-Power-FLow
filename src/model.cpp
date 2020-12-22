#include "model.hpp"

#include <iostream>

model::model(std::vector<bus> busses, std::vector<line> lines)
    : _n_busses(busses.size()), _busses(busses), _lines(lines) {
  _admit.resize(_n_busses, _n_busses);
  std::for_each(lines.begin(), lines.end(), [&](line &i) {
    _admit(i._from_bus, i._from_bus) += (std::complex<double>(1, 0) / i._z);
    _admit(i._from_bus, i._to_bus) = (std::complex<double>(-1, 0) / i._z);
    _admit(i._to_bus, i._to_bus) += (std::complex<double>(1, 0) / i._z);
    _admit(i._to_bus, i._from_bus) = (std::complex<double>(-1, 0) / i._z);
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
    _admit(i._from_bus, i._from_bus) += (std::complex<double>(1, 0) / i._z) + i._shunt_admit[0] ;
    _admit(i._from_bus, i._to_bus) += (std::complex<double>(-1, 0) / i._z);
    _admit(i._to_bus, i._to_bus) += (std::complex<double>(1, 0) / i._z) + i._shunt_admit[1];
    _admit(i._to_bus, i._from_bus) += (std::complex<double>(-1, 0) / i._z);
  });

  // std::for_each(_busses.begin(), _busses.end(), [&](bus &i) {
  //   if(i._loads.real() > 0.1 )
  //   _admit(i._number-1, i._number-1) += (std::complex<double>(1, 0) /
  //   i._loads) ;

  // });
  for (size_t i = 0; i < _admit.rows(); i++) {
    /* code */
    for (size_t j = 0; j < _admit.cols(); j++) {
      /* code */
      //  std::cout << _admit(i, j) << ", ";
    }
    //  std::cout << std::endl << "================" << std::endl;
  }
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
