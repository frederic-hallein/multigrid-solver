#include "smoother.hpp"

namespace multigrid::cartesian_1d {
    void jacobi(
        std::vector<double>& v,
        const std::vector<double>& f,
        double h,
        double sigma,
        double omega
    )
    {
        std::size_t n = v.size();
        std::vector<double> v_new = v;

        for (std::size_t i = 1; i < n - 1; ++i) {
            double jacobi_update = helmholtz_stencil(v[i-1], v[i+1], f[i], h, sigma);
            v_new[i] = weighted_update(v[i], jacobi_update, omega);
        }

        v = v_new;
    }

    void gauss_seidel(
        std::vector<double>& v,
        const std::vector<double>& f,
        double h,
        double sigma,
        double omega
    )
    {
        std::size_t n = v.size();
        for (std::size_t i = 1; i < n - 1; ++i) {
            double gauss_seidel_update = helmholtz_stencil(v[i-1], v[i+1], f[i], h, sigma);
            v[i] = weighted_update(v[i], gauss_seidel_update, omega);
        }
    }

    void red_black_gauss_seidel(
        std::vector<double>& v,
        const std::vector<double>& f,
        double h,
        double sigma,
        double omega
    )
    {
        std::size_t n = v.size();
        for (std::size_t i = 1; i < n - 1; i += 2) {
            double odd_update = helmholtz_stencil(v[i-1], v[i+1], f[i], h, sigma);
            v[i] = weighted_update(v[i], odd_update, omega);
        }

        for (std::size_t i = 2; i < n - 1; i += 2) {
            double even_update = helmholtz_stencil(v[i-1], v[i+1], f[i], h, sigma);
            v[i] = weighted_update(v[i], even_update, omega);
        }
    }
}