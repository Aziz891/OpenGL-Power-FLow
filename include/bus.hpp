#ifndef SOME_UNIQUE_NAME_HERE
#define SOME_UNIQUE_NAME_HERE
#include "types.hpp"
enum bus_type {
    pq, pv, slk
};


class bus
{
private:
    /* data */
    
public:
    bus(double value, double value2, std::string name, int number , bus_type type );
    ~bus();
inline std::complex<double> getRect() { return std::polar(voltage, angle);}
double voltage = 1;
double angle = 0;
bus_type _type;
double _p = 0;
double _q = 0;
std::string _name;
pf_rect _loads{0,0};
int _number;

};


#endif
