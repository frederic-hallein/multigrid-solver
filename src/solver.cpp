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

    double L2(const std::vector<double>& v) {
        return std::sqrt(std::inner_product(v.begin(), v.end(), v.begin(), 0.0));
    }

    // TODO : define other norms and pass functions pointers to parameter
    // (See Ch2 p. 16: Matrix Norms)
    double residual_norm(
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
        return L2(r);
    }

    bool is_converged(
        const std::vector<std::vector<double>>& A,
        const std::vector<double>& x,
        const std::vector<double>& b,
        double tol
    )
    {
        return residual_norm(A, x, b) < tol;
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
        double res = 0.0;
        for (int k = 1; k <= K_max; ++k) {
            for (size_t j = 0; j < n; ++j) {
                double sum = std::inner_product(A[j].begin(), A[j].end(), x.begin(), 0.0) - A[j][j] * x[j];
                y[j] = (1.0 / A[j][j]) * (b[j] - sum);
            }

            res = residual_norm(A, y, b);
            if (res < tol) {
                logger::info(
                    "Jacobi method converged in "
                    + std::to_string(k) + " iterations "
                    + "(res=" + std::to_string(res) + ", tol= " + std::to_string(tol) + "): "
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
            + "(res=" + std::to_string(res) + ", tol= " + std::to_string(tol) + "): x = {}", x
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
        if (!check_dimensions(A, x, b, "Gauss-Seidel")) return;

        double res = 0.0;
        for (int k = 1; k <= K_max; ++k) {
            for (size_t j = 0; j < x.size(); ++j) {
                double sum = std::inner_product(A[j].begin(), A[j].end(), x.begin(), 0.0) - A[j][j] * x[j];
                x[j] = (1.0 / A[j][j]) * (b[j] - sum);
            }

            res = residual_norm(A, x, b);
            if (res < tol) {
                logger::info(
                    "Gauss-Seidel method converged in "
                    + std::to_string(k) + " iterations "
                    + "(res=" + std::to_string(res) + ", tol= " + std::to_string(tol) + "): "
                    + "x = {}", x
                );
                return;
            }
        }

        logger::error(
            "Gauss-Seidel method did not converge after "
            + std::to_string(K_max) + " iterations "
            + "(res=" + std::to_string(res) + ", tol= " + std::to_string(tol) + "): x = {}", x
        );
    }
}
