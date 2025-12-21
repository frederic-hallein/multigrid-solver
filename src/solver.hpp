#pragma once
#include <vector>
#include <string>

namespace solver {
    bool validate_dimensions(
        const std::vector<std::vector<double>>& A,
        const std::vector<double>& x,
        const std::vector<double>& b
    );

    double L2(const std::vector<double>& v);

    std::vector<double> residual(
        const std::vector<std::vector<double>>& A,
        const std::vector<double>& x,
        const std::vector<double>& b
    );

    bool is_converged(
        const std::vector<std::vector<double>>& A,
        const std::vector<double>& x,
        const std::vector<double>& b,
        double tol
    );

    void jacobi(
        const std::vector<std::vector<double>>& A,
        std::vector<double>& x,
        const std::vector<double>& b,
        int K_max,
        double tol = 1e-6,
        double omega = 1.0
    );

    void gauss_seidel(
        const std::vector<std::vector<double>>& A,
        std::vector<double>& x,
        const std::vector<double>& b,
        int K_max,
        double tol = 1e-6,
        double omega = 1.0
    );
}