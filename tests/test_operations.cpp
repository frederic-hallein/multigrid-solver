#include <gtest/gtest.h>

#include "multigrid/cartesian_1d/operations.hpp"

TEST(multigrid_operations, compute_residual) {
    // For u = x(1-x) on [0,1], f = -u'' + 0*u = 2
    double h = 1.0 / 4.0;  // 5 grid points: 0, 0.25, 0.5, 0.75, 1.0
    double sigma = 0.0;

    std::vector<double> v = {0.0, 0.1875, 0.25, 0.1875, 0.0};  // u = x(1-x)
    std::vector<double> f = {0.0, 2.0, 2.0, 2.0, 0.0};

    std::vector<double> r = multigrid::cartesian_1d::compute_residual(v, f, h, sigma);

    // Expected residual: r = f - A*v
    // A*v = (-v[i-1] + 2*v[i] - v[i+1]) / h²
    // For interior points (i=1,2,3): A*v ≈ 2, so r ≈ f - 2 ≈ 0
    EXPECT_EQ(r.size(), v.size());
    EXPECT_NEAR(r[0], 0.0, 1e-10);  // Boundary
    EXPECT_NEAR(r[1], 0.0, 0.1);    // Interior (with tolerance)
    EXPECT_NEAR(r[2], 0.0, 0.1);    // Interior (with tolerance)
    EXPECT_NEAR(r[3], 0.0, 0.1);    // Interior (with tolerance)
    EXPECT_NEAR(r[4], 0.0, 1e-10);  // Boundary
}

TEST(multigrid_operations, restrict_residual) {
    // Fine grid: 9 points (indices 0-8)
    // Coarse grid: 5 points (indices 0-4)
    std::vector<double> residual = {0.0, 1.0, 2.0, 1.0, 2.0, 1.0, 2.0, 1.0, 0.0};

    std::vector<double> coarse_residual = multigrid::cartesian_1d::restrict_residual(residual);

    // Expected size: 9 / 2 + 1 = 5
    EXPECT_EQ(coarse_residual.size(), 5);

    // Boundary residuals should be zero
    EXPECT_NEAR(coarse_residual[0], 0.0, 1e-10);
    EXPECT_NEAR(coarse_residual[4], 0.0, 1e-10);

    // coarse[1] = (1/4)*(residual[1] + 2*residual[2] + residual[3])
    //           = (1/4)*1.0 + (1/2)*2.0 + (1/4)*1.0 = 1.5
    double expected_1 = 0.25 * 1.0 + 0.5 * 2.0 + 0.25 * 1.0;
    EXPECT_NEAR(coarse_residual[1], expected_1, 1e-10);

    // coarse[2] = (1/4)*(residual[3] + 2*residual[4] + residual[5])
    //           = (1/4)*1.0 + (1/2)*2.0 + (1/4)*1.0 = 1.5
    double expected_2 = 0.25 * 1.0 + 0.5 * 2.0 + 0.25 * 1.0;
    EXPECT_NEAR(coarse_residual[2], expected_2, 1e-10);

    // coarse[3] = (1/4)*(residual[5] + 2*residual[6] + residual[7])
    //           = (1/4)*1.0 + (1/2)*2.0 + (1/4)*1.0 = 1.5
    double expected_3 = 0.25 * 1.0 + 0.5 * 2.0 + 0.25 * 1.0;
    EXPECT_NEAR(coarse_residual[3], expected_3, 1e-10);
}

TEST(multigrid_operations, prolongate) {
    // Coarse grid: 5 points (indices 0-4)
    // Fine grid: 9 points (indices 0-8)
    std::vector<double> v2h = {0.0, 1.0, 2.0, 1.0, 0.0};

    std::vector<double> vh = multigrid::cartesian_1d::prolongate(v2h);

    // Expected size: 5 * 2 - 1 = 9
    EXPECT_EQ(vh.size(), 9);

    // Coarse points should be copied to even indices
    EXPECT_NEAR(vh[0], v2h[0], 1e-10);
    EXPECT_NEAR(vh[2], v2h[1], 1e-10);
    EXPECT_NEAR(vh[4], v2h[2], 1e-10);
    EXPECT_NEAR(vh[6], v2h[3], 1e-10);
    EXPECT_NEAR(vh[8], v2h[4], 1e-10);

    // Odd indices should be interpolated
    // fine[1] = 0.5 * (coarse[0] + coarse[1]) = 0.5 * (0.0 + 1.0) = 0.5
    EXPECT_NEAR(vh[1], 0.5, 1e-10);

    // fine[3] = 0.5 * (coarse[1] + coarse[2]) = 0.5 * (1.0 + 2.0) = 1.5
    EXPECT_NEAR(vh[3], 1.5, 1e-10);

    // fine[5] = 0.5 * (coarse[2] + coarse[3]) = 0.5 * (2.0 + 1.0) = 1.5
    EXPECT_NEAR(vh[5], 1.5, 1e-10);

    // fine[7] = 0.5 * (coarse[3] + coarse[4]) = 0.5 * (1.0 + 0.0) = 0.5
    EXPECT_NEAR(vh[7], 0.5, 1e-10);
}

TEST(multigrid_operations, prolongate_restrict_roundtrip) {
    // Integration test: restrict then prolongate should approximately recover original
    std::vector<double> original = {0.0, 1.0, 2.0, 1.0, 2.0, 1.0, 2.0, 1.0, 0.0};

    // Restrict fine to coarse
    std::vector<double> coarse = multigrid::cartesian_1d::restrict_residual(original);

    // Prolongate coarse back to fine
    std::vector<double> recovered = multigrid::cartesian_1d::prolongate(coarse);

    // Should have same size
    EXPECT_EQ(recovered.size(), original.size());

    // Coarse points (even indices) should be exactly recovered
    for (std::size_t i = 0; i < coarse.size(); ++i) {
        EXPECT_NEAR(recovered[2*i], coarse[i], 1e-10);
    }
}

TEST(multigrid_operations, direct_solve) {
    // Test with a simple constant RHS
    std::vector<double> f = {0.0, 1.0, 1.0, 1.0, 0.0};
    double h = 0.25;
    double sigma = 1.0;

    std::vector<double> x = multigrid::cartesian_1d::direct_solve(f, h, sigma);

    // Solution should be finite and satisfy boundary conditions
    EXPECT_NEAR(x[0], 0.0, 1e-10);
    EXPECT_NEAR(x[x.size() - 1], 0.0, 1e-10);

    double h_sq = h * h;
    for (std::size_t i = 1; i < x.size() - 1; ++i) {
        double lhs = (-x[i-1] + 2*x[i] - x[i+1]) / h_sq + sigma * x[i];
        EXPECT_NEAR(lhs, f[i], 1e-10);
    }
}

TEST(multigrid_operations, direct_solve_zero_rhs) {
    // Test with zero RHS - solution should be zero everywhere
    std::vector<double> f(5, 0.0);
    double h = 0.25;
    double sigma = 1.0;

    std::vector<double> x = multigrid::cartesian_1d::direct_solve(f, h, sigma);

    for (std::size_t i = 0; i < x.size(); ++i) {
        EXPECT_NEAR(x[i], 0.0, 1e-10);
    }
}