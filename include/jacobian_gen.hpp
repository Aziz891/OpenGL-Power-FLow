#ifndef JACOBIAN_HG
#define JACOBIAN_HG

#include<eigen3/Eigen/Dense>
#include<complex>
#include<vector>
#include"bus.hpp"
#include"model.hpp"

typedef std::complex<double> pf_rect;


// using namespace Eigen;
class jacobian_gen
{
private:
    /* data */
    Eigen::Matrix<pf_rect, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> &_admit;
    std::vector<bus> &_busses;
    size_t _n_pv_busses;
    size_t _n_busses;
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> _jacobian;
    model &_model;
    size_t test_test = 0;
public:
    jacobian_gen(Eigen::Matrix<pf_rect, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> & admit,std::vector<bus> &busses, size_t n_pv_busses, model &model  );
    ~jacobian_gen();
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> get_jacobian();
    void calculate_j1();
    void calculate_j2();
    void calculate_j3();
    void calculate_j4();
    void calculate_js();
    void print_jacobians();
};

#endif

