#include <cmath>

#include "common/io.hpp"
#include "common/norm.hpp"
#include "common/logger.hpp"
#include "multigrid/cartesian_1d/run.hpp"
#include "setup.hpp"

double f(double x) { return 4.0 * M_PI * M_PI * sin(2 * M_PI * x); }

double u_exact(double x) { return sin(2 * M_PI * x); }

double u_guess(double x) { return 0.0; }

double zero_boundary(double x) { return 0.0; }

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
    Domain1D dom{0.0, 1.0};
    BoundaryCond1D bc{zero_boundary, zero_boundary};

    Config config;
    try {
        config = load_config("../data/config.yaml");

        logger::info("---- Configuration Summary ----");
        logger::info("- sub intervals: {}", config.sub_int);
        logger::info("- num iterations: {}", config.num_iter);
        logger::info("- tolerance: {}", config.tolerance);
        logger::info("- smoother: {} (omega = {})", config.smoother_name, config.omega);
        logger::info("- cycle: {}({}, {})", config.cycle_name, config.smoother_param.nu_1, config.smoother_param.nu_2);
        logger::info("- norm: {}", config.norm_name);
        logger::info("-------------------------------\n");
    } catch (const std::exception& e) {
        logger::error("Configuration error: {}", e.what());
        return 1;
    }

    auto results = multigrid::cartesian_1d::run(
        f, 0.0, dom, bc, config, u_guess
    );

    if (!results) {
        return 1;
    }

    return 0;
}
