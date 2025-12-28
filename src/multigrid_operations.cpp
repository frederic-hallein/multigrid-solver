#include "multigrid_operations.hpp"

namespace multigrid_operations {
    std::vector<double> compute_residual(
        const std::vector<double>& v,
        const std::vector<double>& f,
        double h,
        double sigma
    )
    {
        std::vector<double> r(f.size(), 0.0);
        for (std::size_t i = 1; i < f.size() - 1; ++i) {
            r[i] = f[i] - operators::cart::helmholtz_1d(v[i-1], v[i], v[i+1], h, sigma);
        }

        return r;
    }

    std::vector<double> restrict_residual(
        const std::vector<double>& vh
    )
    {
        std::size_t coarse_size = vh.size() / 2 + 1;
        std::vector<double> v2h(coarse_size, 0.0);

        // TODO: besides full weighted also allow injection
        for (std::size_t j = 1; j < coarse_size - 1; ++j) {
            v2h[j] = restriction::cart::full_weighted_1d(
                vh[2*j-1],
                vh[2*j],
                vh[2*j+1]
            );
        }

        return v2h;
    }

    std::vector<double> direct_solve(
        const std::vector<double>& f,
        double h,
        double sigma
    )
    {
        std::size_t n = f.size();
        std::vector<double> v(n, 0.0);

        double h_sq = h * h;

        double a = -1.0 / h_sq;           // subdiagonal
        double b =  2.0 / h_sq + sigma;   // diagonal
        double c = -1.0 / h_sq;           // superdiagonal

        // Forward elimination
        std::vector<double> c_prime(n);
        std::vector<double> d_prime(n);

        c_prime[0] = c / b;
        d_prime[0] = f[0] / b;

        for (std::size_t i = 1; i < n; ++i) {
            double denom = b - a * c_prime[i - 1];
            if (i < n - 1) {
                c_prime[i] = c / denom;
            }

            d_prime[i] = (f[i] - a * d_prime[i-1]) / denom;
        }

        // Back substitution
        v[n-1] = d_prime[n-1];
        for (int i = n - 2; i >= 0; --i) {
            v[i] = d_prime[i] - c_prime[i] * v[i+1];
        }

        v[0] = 0.0;
        v[n-1] = 0.0;

        return v;
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
}