#include "cycle.hpp"

namespace {
    void v_cycle_recursive(
        std::vector<Grid>& grids,
        std::size_t level,
        double h,
        double sigma,
        double omega,
        const Smoother& smoother,
        const SmootherParam& smoother_param
    )
    {
        logger::info("Running V-Cycle (level = {})", level);
        auto& grid = grids[level];

        if (level == grids.size() - 1) {
            logger::info("Reached coarsest grid. Directly solve for v.");
            grid.v = multigrid_operations::direct_solve(grid.f, h, sigma);
            return;
        }

        for (unsigned int iter = 1; iter <= smoother_param.nu_1; ++iter) {
            logger::info("Pre-smoothing ({}/{})", iter, smoother_param.nu_1);
            smoother(grid.v, grid.f, h, sigma, omega);
        }

        logger::info("Coarsest grid not reached. Call V-Cycle recursively.");
        std::vector<double> residual = multigrid_operations::compute_residual(grid.v, grid.f, h, sigma);
        grids[level + 1].f = multigrid_operations::restrict_residual(residual);

        std::fill(grids[level + 1].v.begin(), grids[level + 1].v.end(), 0.0);

        v_cycle_recursive(grids, level + 1, 2 * h, sigma, omega, smoother, smoother_param);

        logger::info("Prolongating and correcting (level = {})", level);
        std::vector<double> correction = multigrid_operations::prolongate(grids[level + 1].v);
        for (size_t i = 0; i < grid.v.size(); ++i) {
            grid.v[i] += correction[i];
        }

        for (unsigned int iter = 1; iter <= smoother_param.nu_2; ++iter) {
            logger::info("Post-smoothing ({}/{})", iter, smoother_param.nu_2);
            smoother(grid.v, grid.f, h, sigma, omega);
        }
    }
}

namespace cycle {
    void V(
        std::vector<Grid>& grids,
        double h,
        double sigma,
        double omega,
        const Smoother& smoother,
        const SmootherParam& smoother_param
    )
    {
        v_cycle_recursive(grids, 0, h, sigma, omega, smoother, smoother_param);
    }
}