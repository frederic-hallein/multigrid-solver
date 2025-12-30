#pragma once

#include <vector>

#include "grid.hpp"
#include "FDM.hpp"

namespace smoother_1d {
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
    //     double omega = 1.0
    // );

    // void red_black_gauss_seidel(
    //     std::vector<double>& v,
    //     const std::vector<double>& f,
    //     double h,
    //     double sigma,
    //     double omega = 1.0
    // );
}