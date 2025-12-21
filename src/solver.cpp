#include <vector>
#include <cmath>
#include <numeric>

#include "logger.hpp"
#include "solver.hpp"

namespace solver {
    bool validate_dimensions(
        const std::vector<std::vector<double>>& A,
        const std::vector<double>& x,
        const std::vector<double>& b
    )
    {
        size_t n = x.size();
        return (A.size() == n && b.size() == n);
    }

    // TODO : define other norms
    // (See Ch2 p. 16: Matrix Norms)
    double L2(const std::vector<double>& v) {
        return std::sqrt(std::inner_product(v.begin(), v.end(), v.begin(), 0.0));
    }

    std::vector<double> residual(
        const std::vector<std::vector<double>>& A,
        const std::vector<double>& x,
        const std::vector<double>& b
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
        return r;
    }

    bool is_converged(
        const std::vector<std::vector<double>>& A,
        const std::vector<double>& x,
        const std::vector<double>& b,
        double tol
    )
    {
        return L2(residual(A, x, b)) < tol;
    }

    void jacobi(
        const std::vector<std::vector<double>>& A,
        std::vector<double>& x,
        const std::vector<double>& b,
        int K_max,
        double tol
    )
    {
        if (!validate_dimensions(A, x, b)) {
            logger::error(
                "Dimensions mismatch in Jacobi input: "
                "A.size() = " + std::to_string(A.size()) +
                ", x.size() = " + std::to_string(x.size()) +
                ", b.size() = " + std::to_string(b.size())
            );
            return;
        }

        size_t n = x.size();
        std::vector<double> y(n);
        double res_norm = 0.0;
        for (int k = 1; k <= K_max; ++k) {
            for (size_t j = 0; j < n; ++j) {
                double sum = std::inner_product(A[j].begin(), A[j].end(), x.begin(), 0.0) - A[j][j] * x[j];
                y[j] = (1.0 / A[j][j]) * (b[j] - sum);
            }

            res_norm = L2(residual(A, y, b));
            if (res_norm < tol) {
                logger::info(
                    "Jacobi method converged in "
                    + std::to_string(k) + " iterations "
                    + "(res=" + std::to_string(res_norm) + ", tol= " + std::to_string(tol) + "): "
                    + "x = {}", x
                );
                x = y;
                return;
            }

            x = y;
        }

        logger::error(
            "Jacobi method did not converge after "
            + std::to_string(K_max) + " iterations "
            + "(res=" + std::to_string(res_norm) + ", tol= " + std::to_string(tol) + "): "
            + "x = {}", x
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
        if (!validate_dimensions(A, x, b)) {
            logger::error(
                "Dimensions mismatch in Gauss-Seidel input: "
                "A.size() = " + std::to_string(A.size()) +
                ", x.size() = " + std::to_string(x.size()) +
                ", b.size() = " + std::to_string(b.size())
            );
            return;
        }

        double res_norm = 0.0;
        for (int k = 1; k <= K_max; ++k) {
            for (size_t j = 0; j < x.size(); ++j) {
                double sum = std::inner_product(A[j].begin(), A[j].end(), x.begin(), 0.0) - A[j][j] * x[j];
                x[j] = (1.0 / A[j][j]) * (b[j] - sum);
            }

            res_norm = L2(residual(A, x, b));
            if (res_norm < tol) {
                logger::info(
                    "Gauss-Seidel method converged in "
                    + std::to_string(k) + " iterations "
                    + "(res=" + std::to_string(res_norm) + ", tol= " + std::to_string(tol) + "): "
                    + "x = {}", x
                );
                return;
            }
        }

        logger::error(
            "Gauss-Seidel method did not converge after "
            + std::to_string(K_max) + " iterations "
            + "(res=" + std::to_string(res_norm) + ", tol= " + std::to_string(tol) + "): "
            + "x = {}", x
        );
    }
}
