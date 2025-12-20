#include <vector>
#include <cmath>
#include <numeric>

#include "logger.hpp"

bool is_converged(
    const std::vector<std::vector<double>>& A,
    const std::vector<double>& x,
    const std::vector<double>& b,
    double tol = 1e-6
)
{
    std::vector<double> r(b.size());
    for (size_t i = 0; i < b.size(); ++i) {
        double Ax = 0.0;
        for (size_t j = 0; j < x.size(); ++j) {
            Ax += A[i][j] * x[j];
        }
        r[i] = b[i] - Ax;
    }

    double norm = std::sqrt(std::inner_product(r.begin(), r.end(), r.begin(), 0.0));
    return norm < tol;
}

void jacobi(
    const std::vector<std::vector<double>>& A,
    std::vector<double>& x,
    const std::vector<double>& b,
    int K_max,
    double tol
)
{
    std::vector<double> y(b.size());
    for (int k = 1; k < K_max + 1; ++k) {
        for (size_t j = 0; j < x.size(); ++j) {
            double sum = std::inner_product(A[j].begin(), A[j].end(), x.begin(), 0.0);
            y[j] = x[j] - (1.0 / A[j][j]) * (sum - b[j]);
        }

        if (is_converged(A, x, b, tol)) {
            logger::info("Jacobi method convergences: x = {}", x);
            return;
        }

        for (size_t j = 0; j < x.size(); ++j) {
            x[j] = y[j];
        }
    }

    logger::error("Jacobi method did not convergence: x = {}", x);
}
