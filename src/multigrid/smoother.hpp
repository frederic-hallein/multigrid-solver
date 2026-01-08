#pragma once

#include <vector>

namespace {
    inline double helmholtz_stencil_1d(
        double v_x_neg, double v_x_pos,
        double f, double h, double sigma
    )
    {
        return (v_x_neg + v_x_pos + h*h * f) / (2.0 + sigma * h*h);
    }

    inline double helmholtz_stencil_2d(
        double v_x_neg, double v_x_pos,
        double v_y_neg, double v_y_pos,
        double f, double h_x, double h_y, double sigma
    )
    {
        double coeff_x = 1.0 / (h_x * h_x);
        double coeff_y = 1.0 / (h_y * h_y);
        double sum_coeffs = 2.0 * (coeff_x + coeff_y);

        return (coeff_x * (v_x_neg + v_x_pos) + coeff_y * (v_y_neg + v_y_pos) + f) / (sum_coeffs + sigma);
    }

    inline double weighted_update(
        double v_old,
        double v_new,
        double omega
    )
    {
        return (1.0 - omega) * v_old + omega * v_new;
    }
}

namespace multigrid::cart_1d {
    void jacobi(
        std::vector<double>& v,
        const std::vector<double>& f,
        double h,
        double sigma,
        double omega
    );

    void gauss_seidel(
        std::vector<double>& v,
        const std::vector<double>& f,
        double h,
        double sigma,
        double omega
    );

    void red_black_gauss_seidel(
        std::vector<double>& v,
        const std::vector<double>& f,
        double h,
        double sigma,
        double omega
    );
}

namespace multigrid::cart_2d {
    void jacobi(
        std::vector<std::vector<double>>& v,
        const std::vector<std::vector<double>>& f,
        double h,
        double sigma,
        double omega
    );

    void gauss_seidel(
        std::vector<std::vector<double>>& v,
        const std::vector<std::vector<double>>& f,
        double h,
        double sigma,
        double omega
    );

    void red_black_gauss_seidel(
        std::vector<std::vector<double>>& v,
        const std::vector<std::vector<double>>& f,
        double h,
        double sigma,
        double omega
    );
}