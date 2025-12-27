#include "smoother.hpp"

// TODO : general function for looping smoothin params

namespace smoother_1d {
    void jacobi(
        std::vector<double>& v,
        const std::vector<double>& f,
        double h,
        double sigma,
        double omega
    )
    {
        size_t n = v.size();
        std::vector<double> v_new(n);
        for (unsigned int i = 1; i < n - 1; ++i) {
            v_new[i] = stencil::helmholtz_1d(v[i-1], v[i+1], f[i], h, sigma);
        }
        v = v_new;
    }
}

namespace smoother_2d {
    // void jacobi(
    //     const Grid& grid,
    //     double h,
    //     double sigma,
    //     double omega
    // )
    // {
    //     // TODO
    // }
}