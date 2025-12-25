#pragma once

#include <cstddef>
#include <vector>

#include "stencils.hpp"

namespace smoother_1d {
    void jacobi(
        std::vector<double>& v,
        const std::vector<double>& f,
        double h,
        double sigma,
        double omega = 1.0,
        unsigned int num_sweeps = 1
    );

    void gauss_seidel(
        std::vector<double>& v,
        const std::vector<double>& f,
        double h,
        double sigma,
        double omega = 1.0,
        unsigned int num_sweeps = 1
    );

    void red_black_gauss_seidel(
        std::vector<double>& v,
        const std::vector<double>& f,
        double h,
        double sigma,
        double omega = 1.0,
        unsigned int num_sweeps = 1
    );
}
namespace smoother_2d {
    void jacobi(
        std::vector<double>& v,
        const std::vector<double>& f,
        double h,
        double sigma,
        double omega = 1.0,
        unsigned int num_sweeps = 1
    );

    void gauss_seidel(
        std::vector<double>& v,
        const std::vector<double>& f,
        double h,
        double sigma,
        double omega = 1.0,
        unsigned int num_sweeps = 1
    );

    void red_black_gauss_seidel(
        std::vector<double>& v,
        const std::vector<double>& f,
        double h,
        double sigma,
        double omega = 1.0,
        unsigned int num_sweeps = 1
    );
}