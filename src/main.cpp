#include <cmath>

#include "logger.hpp"
#include "common/io.hpp"
#include "multigrid/cartesian_1d/run.hpp"


double f(double x) {
    return 4.0 * M_PI * M_PI * sin(2 * M_PI * x);
}

// double u_exact(double x) {
//     return sin(2 * M_PI * x);
// }

double u_guess(double x) {
    return 0.0;
}

double zero_boundary(double x) {
    return 0.0;
}

// double f(double x) {
//     // -u'' = f  =>  u'' + f = 0
//     // For u(x) = x(1-x), u'' = -2
//     // So f(x) = 2
//     return 2.0;
// }

// double u_exact(double x) {
//     return x * (1.0 - x);
// }

// double u_guess(double x) {
//     return 0.0;
// }

// double zero_boundary(double x) {
//     return 0.0;
// }

int main() {
    unsigned int sub_int = 64; // #subintervals -> n + 1 grid points
    Domain1D dom{ 0.0, 1.0 };
    BoundaryCond1D bc{ zero_boundary, zero_boundary };
    SmootherParam smoother_param{ 3, 3 };
    double sigma = 0.0;

    unsigned int num_iterations = 100;
    double tolerance = 1e-8;

    auto results = multigrid::cartesian_1d::run(
        f, bc, sigma, dom, sub_int, num_iterations, tolerance, u_guess,
        smoother_param, multigrid::cartesian_1d::red_black_gauss_seidel, // TODO: put inside another namespace
        2.0/3.0, multigrid::cartesian_1d::V // TODO: put inside another namespace
    );

    save_solutions_csv("../data/solutions.csv", results.iter, results.v);
    save_residuals_norm_csv("../data/residuals_norm.csv", results.iter, results.residual_norm); // TODO : calculate error norms inside this function instead of Python

    return 0;
}