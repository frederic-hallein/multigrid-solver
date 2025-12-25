#include "smoother.hpp"

namespace smoother {
    // void jacobi_1d(
    //     std::vector<double>& v,
    //     const std::vector<double>& f,
    //     double alpha,
    //     unsigned int num_sweeps
    // )
    // {
    //     size_t n = v.size();
    //     for (unsigned int iter = 0; iter < num_sweeps; ++iter) {
    //         std::vector<double> v_new(n);
    //         for (unsigned int i = 1; i < n - 1; ++i) {
    //             // TODO : use stencil
    //             v_new[i] = stencils::helmholtz_1d(v[i-1], v[i+1], f[i], h, alpha);
    //         }
    //         v = v_new;
    //     }
    // }

    // void jacobi_2d(
    //     std::vector<double>& v,
    //     const std::vector<double>& f,
    //     unsigned int num_sweeps
    // )
    // {
    //     std::vector<double> v_new(v.size());
    //     for (unsigned int i = 0; i < n; ++i) {
    //         for (unsigned int j = 0; j < n; ++j) {
    //             // TODO : handle BC

    //             // TODO : use stencil
    //         }
    //     }
    //     v = v_new;
    // }
}