#pragma once

#include <cmath>
#include <vector>

#include "operators.hpp"
#include "restriction.hpp"

namespace multigrid_operations {
    std::vector<double> compute_residual(
        const std::vector<double>& v,
        const std::vector<double>& f,
        double h,
        double sigma
    );

    std::vector<double> restrict_residual(
        const std::vector<double>& vh
    );

    std::vector<double> direct_solve(
        const std::vector<double>& f,
        double h,
        double sigma
    );

    std::vector<double> prolongate(
        const std::vector<double>& v2h
    );
}