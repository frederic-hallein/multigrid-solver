#include <cmath>

#include "logger.hpp"
#include "multigrid.hpp"


// double f(double x, double y) {
//     return 2.0 * ((1.0 - 6.0 * x*x) * y*y * (1.0 - y*y) + (1.0 - 6 * y*y) * x*x * (1.0 - x*x));
// }

// double u_guess(double x, double y) {
//     return 0.0;
// }

// double u_exact(double x, double y) {
//     return x*x * y*y * (1.0 - x*x) * (y*y - 1.0);
// }

// double zero_boundary(double x, double y) {
//     return 0.0;
// }

double f(double x) {
    return M_PI * M_PI * sin(M_PI * x);
}

double u_exact(double x) {
    return sin(M_PI * x);
}

double u_guess(double x) {
    return 0.0;
}

double zero_boundary(double x) {
    return 0.0;
}

int main() {
    unsigned int sub_int = 16; // #subintervals -> n + 1 grid points
    Domain1D dom{ 0.0, 1.0 };
    BoundaryCond1D bc{ zero_boundary, zero_boundary };
    SmootherParam smoother_param{ 3, 3 };
    double sigma = 0.0;

    // TODO : return struct object containing all info from MG instead of only solution u
    std::vector<double> u = multigrid::run_helmholtz_cartesian_1d(
        f,
        bc,
        sigma,
        dom,
        sub_int,
        u_guess,
        smoother_param
    );

    logger::info("u = {}", u);


    return 0;
}