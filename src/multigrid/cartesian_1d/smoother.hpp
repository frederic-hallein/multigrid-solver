#pragma once

#include <vector>

#include "grid.hpp"

namespace {
    inline double helmholtz_stencil(
        double v_x_neg, double v_x_pos,
        double f, double h, double sigma
    )
    {
        return (v_x_neg + v_x_pos + h*h * f) / (2.0 + sigma * h*h);
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
namespace multigrid::cartesian_1d::smoother {
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