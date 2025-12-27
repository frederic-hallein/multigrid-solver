#pragma once

#include <vector>

namespace multigrid_operations {
    std::vector<double> compute_residual(
        const std::vector<double>& f,
        double h
    );

    std::vector<double> restrict_residual(
        const std::vector<double>& residual
    );

    std::vector<double> direct_solve(
        const std::vector<double>& f,
        double h
    );

    std::vector<double> prolongate(
        const std::vector<double>& coarse_correction
    );
}