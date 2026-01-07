#include "operations.hpp"

namespace multigrid {
    std::vector<double> compute_residual(
        const std::vector<double>& v,
        const std::vector<double>& f,
        double h,
        double sigma
    )
    {
        std::vector<double> r(f.size(), 0.0);
        for (std::size_t i = 1; i < f.size() - 1; ++i) {
            r[i] = f[i] - (-v[i-1] + 2 * v[i] - v[i+1]) / (h*h) + sigma * v[i];
        }

        return r;
    }

    std::vector<double> restrict_residual(
        const std::vector<double>& vh
    )
    {
        std::size_t coarse_size = vh.size() / 2 + 1;
        std::vector<double> v2h(coarse_size, 0.0);

        // full weighted
        for (std::size_t j = 1; j < coarse_size - 1; ++j) {
            v2h[j] = (vh[2*j-1] + 2 * vh[2*j] + vh[2*j+1]) / 4.0;
        }

        return v2h;
    }

    std::vector<double> prolongate(
        const std::vector<double>& v2h
    )
    {
        std::size_t fine_size = v2h.size() * 2 - 1;
        std::vector<double> vh(fine_size, 0.0);

        for (std::size_t j = 0; j < v2h.size(); ++j) {
            vh[2*j] = v2h[j];

            if (j < v2h.size() - 1) {
                vh[2*j+1] = 0.5 * (v2h[j] + v2h[j+1]);
            }
        }

        return vh;
    }

    std::vector<double> direct_solve(
        const std::vector<double>& f,
        double h,
        double sigma
    )
    {
        std::size_t n = f.size();
        std::vector<double> x(n, 0.0);

        // build tridiagonal system matrix and RHS
        std::vector<std::vector<double>> A(n, std::vector<double>(n, 0.0));
        std::vector<double> b = f;

        // construct the discrete Helmholtz operator matrix
        for (std::size_t i = 0; i < n; ++i) {
            if (i == 0 || i == n - 1) {
                // boundary conditions: Dirichlet (homogeneous)
                A[i][i] = 1.0;
                b[i] = 0.0;
            } else {
                // interior points: discrete Helmholtz stencil
                double h_sq = h * h;
                A[i][i-1] = -1.0 / h_sq;
                A[i][i]   =  2.0 / h_sq + sigma;
                A[i][i+1] = -1.0 / h_sq;
            }
        }

        // gaussian elimination with partial pivoting
        for (std::size_t k = 0; k < n - 1; ++k) {
            // find pivot
            std::size_t pivot = k;
            for (std::size_t i = k + 1; i < n; ++i) {
                if (std::abs(A[i][k]) > std::abs(A[pivot][k])) {
                    pivot = i;
                }
            }

            // swap rows
            if (pivot != k) {
                std::swap(A[k], A[pivot]);
                std::swap(b[k], b[pivot]);
            }

            // elimination
            for (std::size_t i = k + 1; i < n; ++i) {
                if (std::abs(A[k][k]) < 1e-14) continue;
                double factor = A[i][k] / A[k][k];
                for (std::size_t j = k; j < n; ++j) {
                    A[i][j] -= factor * A[k][j];
                }
                b[i] -= factor * b[k];
            }
        }

        // back substitution
        for (int i = n - 1; i >= 0; --i) {
            x[i] = b[i];
            for (std::size_t j = i + 1; j < n; ++j) {
                x[i] -= A[i][j] * x[j];
            }
            if (std::abs(A[i][i]) > 1e-14) {
                x[i] /= A[i][i];
            }
        }

        return x;
    }
}