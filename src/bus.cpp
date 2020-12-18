#include "bus.hpp"

bus::bus(double value, double value2, std::string name, int nuumber, bus_type type)
    : voltage(value), angle(value2), _name(name), _number(nuumber), _type(type) {}

bus::~bus() {}
