#include <vector>
#include <cmath>
#include <numeric>

#include "logger.hpp"
#include "solver.hpp"

namespace solver {
    bool check_dimensions(
        const std::vector<std::vector<double>>& A,
        const std::vector<double>& x,
        const std::vector<double>& b,
        const std::string& method_name)
    {
        size_t n = x.size();
        if (A.size() != n || b.size() != n) {
            logger::error("Dimensions mismatch in " + method_name + " input.");
            return false;
        }
        return true;
    }

    bool is_converged(
        const std::vector<std::vector<double>>& A,
        const std::vector<double>& x,
        const std::vector<double>& b,
        double tol
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
        if (!check_dimensions(A, x, b, "Jacobi")) return;

        size_t n = x.size();
        std::vector<double> y(n);
        for (int k = 1; k <= K_max; ++k) {
            for (size_t j = 0; j < n; ++j) {
                double sum = std::inner_product(A[j].begin(), A[j].end(), x.begin(), 0.0) - A[j][j] * x[j];
                y[j] = (1.0 / A[j][j]) * (b[j] - sum);
            }

            if (is_converged(A, y, b, tol)) {
                logger::info("Jacobi method converged in " + std::to_string(k) + " iterations: x = {}", y);
                x = y;
                return;
            }

            x = y;
        }

        logger::error(
            "Jacobi method did not converge after "
            + std::to_string(K_max)
            + " iterations (tol=" + std::to_string(tol) + "): x = {}", x
        );
    }

    void gauss_seidel(
        const std::vector<std::vector<double>>& A,
        std::vector<double>& x,
        const std::vector<double>& b,
        int K_max,
        double tol
    )
    {
        if (!check_dimensions(A, x, b, "Jacobi")) return;

        for (int k = 1; k <= K_max; ++k) {
            for (size_t j = 0; j < x.size(); ++j) {
                double sum = std::inner_product(A[j].begin(), A[j].end(), x.begin(), 0.0) - A[j][j] * x[j];
                x[j] = (1.0 / A[j][j]) * (b[j] - sum);
            }

            if (is_converged(A, x, b, tol)) {
                logger::info(
                    "Gauss-Seidel method converged in "
                    + std::to_string(k)
                    + " iterations: x = {}", x)
                ;
                return;
            }
        }

        logger::error(
            "Gauss-Seidel method did not converge after "
            + std::to_string(K_max)
            + " iterations (tol=" + std::to_string(tol) + "): x = {}", x
        );
    }
}
