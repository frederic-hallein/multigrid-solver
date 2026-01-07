#include "smoother.hpp"

namespace multigrid::cart_1d {
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
            double jacobi_update = helmholtz_stencil_1d(v[i-1], v[i+1], f[i], h, sigma);
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
            double gauss_seidel_update = helmholtz_stencil_1d(v[i-1], v[i+1], f[i], h, sigma);
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
            double odd_update = helmholtz_stencil_1d(v[i-1], v[i+1], f[i], h, sigma);
            v[i] = weighted_update(v[i], odd_update, omega);
        }

        for (std::size_t i = 2; i < n - 1; i += 2) {
            double even_update = helmholtz_stencil_1d(v[i-1], v[i+1], f[i], h, sigma);
            v[i] = weighted_update(v[i], even_update, omega);
        }
    }
}

namespace multigrid::cart_2d {
    void jacobi(
        std::vector<std::vector<double>>& v,
        const std::vector<std::vector<double>>& f,
        double h_x,
        double h_y,
        double sigma,
        double omega
    )
    {
        std::size_t nx = v.size();
        std::size_t ny = v[0].size();
        std::vector<std::vector<double>> v_new = v;
        for (std::size_t i = 1; i < nx - 1; ++i) {
            for (std::size_t j = 1; j < ny - 1; ++j) {
                double jacobi_update = helmholtz_stencil_2d(
                    v[i-1][j], v[i+1][j],
                    v[i][j-1], v[i][j+1],
                    f[i][j], h_x, h_y, sigma
                );
                v_new[i][j] = weighted_update(v[i][j], jacobi_update, omega);
            }
        }
        v = v_new;
    }

    void gauss_seidel(
        std::vector<std::vector<double>>& v,
        const std::vector<std::vector<double>>& f,
        double h_x,
        double h_y,
        double sigma,
        double omega
    )
    {
        std::size_t nx = v.size();
        std::size_t ny = v[0].size();
        for (std::size_t i = 1; i < nx - 1; ++i) {
            for (std::size_t j = 1; j < ny - 1; ++j) {
                double gauss_seidel_update = helmholtz_stencil_2d(
                    v[i-1][j], v[i+1][j],
                    v[i][j-1], v[i][j+1],
                    f[i][j], h_x, h_y, sigma
                );
                v[i][j] = weighted_update(v[i][j], gauss_seidel_update, omega);
            }
        }
    }

    void red_black_gauss_seidel(
        std::vector<std::vector<double>>& v,
        const std::vector<std::vector<double>>& f,
        double h_x,
        double h_y,
        double sigma,
        double omega
    )
    {
        std::size_t nx = v.size();
        std::size_t ny = v[0].size();
        for (std::size_t i = 1; i < nx - 1; ++i) {
            for (std::size_t j = 1; j < ny - 1; ++j) {
                if ((i + j) % 2 == 0) {
                    double odd_update = helmholtz_stencil_2d(
                        v[i-1][j], v[i+1][j],
                        v[i][j-1], v[i][j+1],
                        f[i][j], h_x, h_y, sigma
                    );
                    v[i][j] = weighted_update(v[i][j], odd_update, omega);
                }
            }
        }

        for (std::size_t i = 1; i < nx - 1; ++i) {
            for (std::size_t j = 1; j < ny - 1; ++j) {
                if ((i + j) % 2 == 1) {
                    double even_update = helmholtz_stencil_2d(
                        v[i-1][j], v[i+1][j],
                        v[i][j-1], v[i][j+1],
                        f[i][j], h_x, h_y, sigma
                    );
                    v[i][j] = weighted_update(v[i][j], even_update, omega);
                }
            }
        }
    }
}