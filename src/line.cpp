#include "line.hpp"

line::line() {}
line::line(int number, int from_bus, int to_bus, std::complex<double> z, std::vector<std::complex<double>> shunt_admit  )
    : _from_bus(from_bus), _to_bus(to_bus), _z(z), _shunt_admit(shunt_admit), _number(number) {

        
    }

line::~line() {}
