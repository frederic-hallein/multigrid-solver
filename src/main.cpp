#include <iostream>
#include <functional>
#include <cmath>

#include "logger.hpp"
#include "alias.hpp"
#include "multigrid.hpp"
#include "domain.hpp"
#include "smoother.hpp"



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
    return std::sin(M_PI * x);
}

double u_guess(double x) {
    return 0.0;
}

double zero_boundary(double x) {
    return 0.0;
}

int main() {
    unsigned int sub_int = 16; // #subintervals -> n + 1 grid points
    Domain1D domain{ 0.0, 1.0 };
    BoundaryCond1D bc{ zero_boundary, zero_boundary };
    SmootherParam smoother_param{ 2, 1 };
    double alpha = 0.0;

    // TODO : just stick to procedural programming and 1D for now
    multigrid::run_helmholtz_1d(
        f,
        bc,
        alpha,
        domain,
        sub_int,
        u_guess,
        smoother_param,
        smoother_1d::jacobi,
        cycle::v_cycle
    );



    return 0;
}