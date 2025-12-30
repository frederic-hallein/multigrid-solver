#include "multigrid.hpp"

namespace multigrid {
    std::vector<double> run_helmholtz_cartesian_1d(
        Func1D rhs_f,
        BoundaryCond1D bc,
        double sigma,
        Domain1D dom,
        unsigned int sub_int,
        unsigned int num_iterations,
        double tolerance,
        Func1D u_guess,
        const SmootherParam& smoother_param,
        const Smoother& smoother,
        double omega,
        Cycle cycle
    )
    {
        if (sub_int % 2 != 0) {
            logger::error("Sub intervals are not a multiple of 2.");
            return {};
        }

        std::vector<Grid> grids = initialize_grids(rhs_f, u_guess, dom, bc, sub_int);

        double h = (dom.x_max - dom.x_min) / sub_int;
        for (int iter = 0; iter < num_iterations; ++iter) {
            cycle(grids, 0, h, sigma, omega, smoother, smoother_param);

            auto r = multigrid_operations::compute_residual(grids[0].v, grids[0].f, h, sigma);
            double residual_norm = norm::L2(r);
            if (residual_norm < tolerance) {
                logger::info("Converged at iteration step {}", iter);
                return grids[0].v;
            }
        }

        return {};
    }
}