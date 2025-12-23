#include <iostream>
#include <functional>

#include "logger.hpp"
#include "multigrid.hpp"



double f(double x, double y) {
    return 2.0 * ((1.0 - 6.0 * x*x) * y*y * (1.0 - y*y) + (1.0 - 6 * y*y) * x*x * (1.0 - x*x));
}

double u_guess(double x, double y) {
    return 0.0;
}

double u_exact(double x, double y) {
    return x*x * y*y * (1.0 - x*x) * (y*y - 1.0);
}

double zero_boundary(double x, double y) {
    return 0.0;
}

int main() {
    unsigned int n = 16; // # grid points
    double x_min = 0.0, x_max = 1.0;
    double y_min = 0.0, y_max = 1.0;
    unsigned int nu_1 = 2;
    unsigned int nu_2 = 1;
    double alpha = 0.0;

    MG mg(f, zero_boundary, x_min, x_max, y_min, y_max, alpha);
    mg.run(n, smoother::SmootherType::RBGS, CycleType::V, nu_1, nu_2, u_guess);


    return 0;
}