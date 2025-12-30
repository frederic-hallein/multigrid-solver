#pragma once

#include <vector>

#include "grid.hpp"

namespace multigrid::cartesian_1d {
    void jacobi(
        std::vector<double>& v,
        const std::vector<double>& f,
        double h,
        double sigma,
        double omega
    );

    // void gauss_seidel(
    //     std::vector<double>& v,
    //     const std::vector<double>& f,
    //     double h,
    //     double sigma,
    //     double omega
    // );

    // void red_black_gauss_seidel(
    //     std::vector<double>& v,
    //     const std::vector<double>& f,
    //     double h,
    //     double sigma,
    //     double omega
    // );
}