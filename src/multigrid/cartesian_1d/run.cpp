#include "run.hpp"

namespace multigrid::cartesian_1d {
    std::vector<double> run(
        const Func1D& rhs_f,
        const BoundaryCond1D& bc,
        double sigma,
        const Domain1D& dom,
        unsigned int sub_int,
        unsigned int num_iterations,
        double tolerance,
        const Func1D& u_guess,
        const SmootherParam& smoother_param,
        const Smoother& smoother,
        double omega,
        const Cycle& cycle
    )
    {
        if (sub_int == 0) {
            logger::error("Sub intervals cannot be 0.");
            return {};
        }

        if (sub_int % 2 != 0) {
            logger::error("Sub intervals are not a multiple of 2.");
            return {};
        }

        std::vector<Grid> grids = init_grids(rhs_f, u_guess, dom, bc, sub_int);

        double h = (dom.x_max - dom.x_min) / sub_int;
        for (int iter = 0; iter < num_iterations; ++iter) {
            cycle(grids, 0, h, sigma, omega, smoother, smoother_param);

            auto r = compute_residual(grids[0].v, grids[0].f, h, sigma);
            double residual_norm = L2(r);

            logger::info("L2(r) = {} at iter = {}", residual_norm, iter);
            if (residual_norm < tolerance) {
                logger::info("Converged at iteration step {}", iter);
                return grids[0].v;
            }
        }

        return {};
    }
}