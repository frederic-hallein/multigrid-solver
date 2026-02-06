#pragma once

#include <cmath>
#include <vector>

namespace multigrid::dim1 {
std::vector<double> compute_residual(
    const std::vector<double>& v,
    const std::vector<double>& f,
    double h,
    double sigma
);

std::vector<double> restrict_residual(
    const std::vector<double>& vh
);

std::vector<double> prolongate(
    const std::vector<double>& v2h
);

std::vector<double> direct_solve(
    const std::vector<double>& f,
    double h,
    double sigma
);
}

namespace multigrid::dim2 {
std::vector<std::vector<double>> compute_residual(
    const std::vector<std::vector<double>>& v,
    const std::vector<std::vector<double>>& f,
    double h_x,
    double h_y,
    double sigma
);

// std::vector<double> restrict_residual(
//     const std::vector<std::vector<double>>& vh
// );

// std::vector<double> prolongate(
//     const std::vector<std::vector<double>>& v2h
// );

// std::vector<double> direct_solve(
//     const std::vector<std::vector<double>>& f,
//     double h_x,
//     double h_y,
//     double sigma
// );
}