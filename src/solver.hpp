#pragma once
#include <vector>
#include <string>

namespace solver {
    bool check_dimensions(
        const std::vector<std::vector<double>>& A,
        const std::vector<double>& x,
        const std::vector<double>& b,
        const std::string& method_name
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
        double tol = 1e-6
    );

    void gauss_seidel(
        const std::vector<std::vector<double>>& A,
        std::vector<double>& x,
        const std::vector<double>& b,
        int K_max,
        double tol = 1e-6
    );
}