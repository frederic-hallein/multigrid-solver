#include <cmath>

#include "logger.hpp"
#include "common/io.hpp"
#include "common/norm.hpp"
#include "multigrid/cartesian_1d/run.hpp"


double f(double x) {
    return 4.0 * M_PI * M_PI * sin(2 * M_PI * x);
}

double u_exact(double x) {
    return sin(2 * M_PI * x);
}

double u_guess(double x) {
    return 0.0;
}

double zero_boundary(double x) {
    return 0.0;
}


// double f(double x) {
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
    double tolerance = 1e-10;

    auto results = multigrid::cartesian_1d::run(
        f, bc, sigma, dom, sub_int, num_iterations, tolerance, u_guess,
        smoother_param,
        multigrid::cartesian_1d::smoother::red_black_gauss_seidel, // TODO : use enums so that python plot can use this to plot
        2.0/3.0,
        multigrid::cartesian_1d::cycle::V, // TODO : use enums so that python plot can use this to plot
        L2 // TODO : use enums so that python plot can use this to plot
    );

    if (!results) {
        logger::error("Did not converge within the maximum number of iterations ({}).", num_iterations);
        return 1;
    }

    // TODO : move inside run() and make u_exact optional with default null
    save_solutions_csv("../data/solutions.csv", results->v);
    save_convergence_history_csv("../data/convergence_history.csv", results->residual_norm, results->v, dom, sub_int, u_exact, L2);

    return 0;
}