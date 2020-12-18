#include <complex>
#include <vector>

#include "bus.hpp"

class line {
 private:
  /* data */
 public:
  int _from_bus;
  int _to_bus;
  std::complex<double> _z;
  std::vector<std::complex<double>> _shunt_admit;
  line(int from_bus, int to_bus, std::complex<double> z, std::vector<std::complex<double>> shunt_admit);
  line();
  ~line();
};
