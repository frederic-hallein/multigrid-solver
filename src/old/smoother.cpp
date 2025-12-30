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
        std::size_t n = v.size();
        std::vector<double> v_new = v; // make copy which keeps boundary values untouched

        for (std::size_t i = 1; i < n - 1; ++i) {
            double jacobi_update = FDM::cart::helmholtz_1d(
                v[i-1], v[i+1], f[i], h, sigma
            );

            // apply weights: v_new = (1-ω)*v + ω*jacobi_update
            v_new[i] = (1.0 - omega) * v[i] + omega * jacobi_update;
        }

        v = v_new;
    }
}