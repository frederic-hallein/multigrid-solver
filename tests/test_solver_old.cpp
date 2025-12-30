// #include <gtest/gtest.h>
// #include "../src/solver_old.hpp"

// TEST(test_jacobi, solves_2x2_system) {
//     std::vector<std::vector<double>> A = {
//         {2, 1},
//         {5, 7}
//     };
//     std::vector<double> b = {11, 13};
//     std::vector<double> x = {1, 1};
//     int K_max = 25;
//     double tol = 1.0;
//     double omega = 2.0 / 3.0;

//     solver::jacobi(A, x, b, K_max, tol, omega);

//     double res_norm = solver::L2(solver::residual(A, x, b));
//     EXPECT_LT(res_norm, tol);
//     EXPECT_NEAR(x[0], 7.111, tol);
//     EXPECT_NEAR(x[1], -3.222, tol);
// }

// TEST(test_gauss_seidel, solves_2x2_system) {
//     std::vector<std::vector<double>> A = {
//         {16, 3},
//         {7, -11}
//     };
//     std::vector<double> b = {11, 13};
//     std::vector<double> x = {1, 1};
//     int K_max = 7;
//     double tol = 1e-3;
//     double omega = 1.0;

//     solver::gauss_seidel(A, x, b, K_max, tol, omega);

//     double res_norm = solver::L2(solver::residual(A, x, b));
//     EXPECT_LT(res_norm, tol);

//     EXPECT_NEAR(x[0], 0.812, tol);
//     EXPECT_NEAR(x[1], -0.665, tol);
// }