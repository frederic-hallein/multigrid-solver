#include <gtest/gtest.h>
#include "../src/solver.hpp"

TEST(test_jacobi, solves_2x2_system) {
    std::vector<std::vector<double>> A = {
        {2, 1},
        {5, 7}
    };
    std::vector<double> b = {11, 13};
    std::vector<double> x = {1, 1};
    solver::jacobi(A, x, b, 25);

    EXPECT_NEAR(x[0], 7.111, 1e-3);
    EXPECT_NEAR(x[1], -3.222, 1e-3);
}

TEST(test_gauss_seidel, solves_2x2_system) {
    std::vector<std::vector<double>> A = {
        {16, 3},
        {7, -11}
    };
    std::vector<double> b = {11, 13};
    std::vector<double> x = {1, 1};
    int K_max = 7;

    solver::gauss_seidel(A, x, b, K_max);

    EXPECT_NEAR(x[0], 0.8122, 1e-4);
    EXPECT_NEAR(x[1], -0.6650, 1e-4);
}