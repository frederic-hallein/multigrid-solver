#include <cmath>

#include "logger.hpp"
#include "multigrid.hpp"


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

int main() {
    unsigned int sub_int = 32; // #subintervals -> n + 1 grid points
    Domain1D dom{ 0.0, 1.0 };
    BoundaryCond1D bc{ zero_boundary, zero_boundary };
    SmootherParam smoother_param{ 3, 3 };
    double sigma = 0.0;

    unsigned int num_iterations = 1000;
    double tolerance = 1e-10;

    // TODO : return struct object containing all info from MG instead of only solution u
    std::vector<double> u = multigrid::run_helmholtz_cartesian_1d(
        f,
        bc,
        sigma,
        dom,
        sub_int,
        num_iterations,
        tolerance,
        u_guess,
        smoother_param,
        smoother_1d::jacobi,
        2.0 / 3.0
    );

    logger::info("u = {}", u);


    return 0;
}