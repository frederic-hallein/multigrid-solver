#include "smoother.hpp"

namespace smoother_1d {
    void jacobi(
        std::vector<double>& v,
        const std::vector<double>& f,
        double h,
        double sigma,
        double omega,
        unsigned int num_sweeps
    )
    {
        size_t n = v.size();
        std::vector<double> v_new(n);
        for (unsigned int i = 1; i < n - 1; ++i) {
            v_new[i] = stencils::helmholtz_1d(v[i-1], v[i+1], f[i], h, sigma);
        }
        v = v_new;
    }
}

namespace smoother_2d {
    void jacobi(
        std::vector<double>& v,
        const std::vector<double>& f,
        double h,
        double sigma,
        unsigned int num_sweeps,
        double omega
    )
    {
        // std::vector<double> v_new(v.size());
        // for (unsigned int i = 0; i < num_sweeps; ++i) {
        //     // TODO
        // }
        // v = v_new;
    }
}