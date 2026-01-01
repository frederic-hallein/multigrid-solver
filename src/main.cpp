#include <cmath>

#include "common/io.hpp"
#include "common/norm.hpp"
#include "logger.hpp"
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

    try {
        Config config = load_config("../data/config.yaml");

        logger::info("=== Configuration summary ===");
        logger::info("- sub_intervals: {}", config.sub_int);
        logger::info("- num_iterations: {}", config.num_iter);
        logger::info("- tolerance: {}", config.tolerance);
        logger::info("- smoother: {}", config.smoother ? "set" : "not set");
        logger::info("- cycle: {}", config.cycle ? "set" : "not set");
        logger::info("- norm: {}", config.norm ? "set" : "not set");
        logger::info("- omega: {}", config.omega);
        logger::info("- pre_iterations: {}", config.smoother_param.nu_1);
        logger::info("- post_iterations: {}", config.smoother_param.nu_2);
        logger::info("=============================");

        auto results = multigrid::cartesian_1d::run(
            f, 0.0, dom, bc, config, u_guess
        );
        if (!results) {
            return 1;
        }

    } catch (const std::exception& e) {
        logger::error("Configuration error: {}", e.what());
        return 1;
    }

    return 0;
}
