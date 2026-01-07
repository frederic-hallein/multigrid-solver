#include "cycle.hpp"

namespace multigrid {
    void v_cycle(
        std::vector<Grid1D>& grids,
        std::size_t level,
        double h,
        double sigma,
        double omega,
        const Smoother& smoother,
        const SmootherParam& smoother_param
    )
    {
        logger::debug("Running V-Cycle (level = {})", level);
        auto& grid = grids[level];

        if (level == grids.size() - 1) {
            logger::debug("Reached coarsest grid. Directly solve for v.");
            grid.v = direct_solve(grid.f, h, sigma);
            return;
        }

        for (unsigned int iter = 1; iter <= smoother_param.nu_1; ++iter) {
            logger::debug("Pre-smoothing ({}/{})", iter, smoother_param.nu_1);
            smoother(grid.v, grid.f, h, sigma, omega);
        }

        logger::debug("Coarsest grid not reached. Call V-Cycle recursively.");
        grids[level + 1].f = restrict_residual(compute_residual(grid.v, grid.f, h, sigma));

        std::fill(grids[level + 1].v.begin(), grids[level + 1].v.end(), 0.0);
        v_cycle(grids, level + 1, 2 * h, sigma, omega, smoother, smoother_param);

        logger::debug("Prolongating and correcting (level = {})", level);
        std::vector<double> correction = prolongate(grids[level + 1].v);
        for (size_t i = 0; i < grid.v.size(); ++i) {
            grid.v[i] += correction[i];
        }

        for (unsigned int iter = 1; iter <= smoother_param.nu_2; ++iter) {
            logger::debug("Post-smoothing ({}/{})", iter, smoother_param.nu_2);
            smoother(grid.v, grid.f, h, sigma, omega);
        }
    }

    void f_cycle(
        std::vector<Grid1D>& grids,
        std::size_t level,
        double h,
        double sigma,
        double omega,
        const Smoother& smoother,
        const SmootherParam& smoother_param
    )
    {
        logger::debug("Running F-Cycle (level = {})", level);
        auto& grid = grids[level];

        if (level == grids.size() - 1) {
            logger::debug("Reached coarsest grid. Directly solve for v.");
            grid.v = direct_solve(grid.f, h, sigma);
            return;
        }

        for (unsigned int iter = 1; iter <= smoother_param.nu_1; ++iter) {
            logger::debug("Pre-smoothing ({}/{})", iter, smoother_param.nu_1);
            smoother(grid.v, grid.f, h, sigma, omega);
        }

        grids[level + 1].f = restrict_residual(compute_residual(grid.v, grid.f, h, sigma));
        std::fill(grids[level + 1].v.begin(), grids[level + 1].v.end(), 0.0);
        f_cycle(grids, level + 1, 2 * h, sigma, omega, smoother, smoother_param);


        std::vector<double> correction = prolongate(grids[level + 1].v);
        for (size_t i = 0; i < grid.v.size(); ++i) {
            grid.v[i] += correction[i];
        }

        for (unsigned int iter = 1; iter <= smoother_param.nu_2; ++iter) {
            logger::debug("Re-smoothing ({}/{})", iter, smoother_param.nu_2);
            smoother(grid.v, grid.f, h, sigma, omega);
        }

        grids[level + 1].f = restrict_residual(compute_residual(grid.v, grid.f, h, sigma));
        std::fill(grids[level + 1].v.begin(), grids[level + 1].v.end(), 0.0);
        v_cycle(grids, level + 1, 2 * h, sigma, omega, smoother, smoother_param);

        correction = prolongate(grids[level + 1].v);
        for (size_t i = 0; i < grid.v.size(); ++i) {
            grid.v[i] += correction[i];
        }

        for (unsigned int iter = 1; iter <= smoother_param.nu_2; ++iter) {
            logger::debug("Post-smoothing ({}/{})", iter, smoother_param.nu_2);
            smoother(grid.v, grid.f, h, sigma, omega);
        }
    }

    void w_cycle(
        std::vector<Grid1D>& grids,
        std::size_t level,
        double h,
        double sigma,
        double omega,
        const Smoother& smoother,
        const SmootherParam& smoother_param
    )
    {
        logger::debug("Running W-Cycle (level = {})", level);
        auto& grid = grids[level];

        if (level == grids.size() - 1) {
            logger::debug("Reached coarsest grid. Directly solve for v.");
            grid.v = direct_solve(grid.f, h, sigma);
            return;
        }

        for (unsigned int iter = 1; iter <= smoother_param.nu_1; ++iter) {
            logger::debug("Pre-smoothing ({}/{})", iter, smoother_param.nu_1);
            smoother(grid.v, grid.f, h, sigma, omega);
        }

        grids[level + 1].f = restrict_residual(compute_residual(grid.v, grid.f, h, sigma));
        std::fill(grids[level + 1].v.begin(), grids[level + 1].v.end(), 0.0);
        w_cycle(grids, level + 1, 2 * h, sigma, omega, smoother, smoother_param);

        logger::debug("Prolongating and correcting (level = {})", level);
        std::vector<double> correction = prolongate(grids[level + 1].v);
        for (size_t i = 0; i < grid.v.size(); ++i) {
            grid.v[i] += correction[i];
        }

        for (unsigned int iter = 1; iter <= smoother_param.nu_2; ++iter) {
            logger::debug("Post-smoothing ({}/{})", iter, smoother_param.nu_2);
            smoother(grid.v, grid.f, h, sigma, omega);
        }

        grids[level + 1].f = restrict_residual(compute_residual(grid.v, grid.f, h, sigma));
        std::fill(grids[level + 1].v.begin(), grids[level + 1].v.end(), 0.0);
        w_cycle(grids, level + 1, 2 * h, sigma, omega, smoother, smoother_param);

        correction = prolongate(grids[level + 1].v);
        for (size_t i = 0; i < grid.v.size(); ++i) {
            grid.v[i] += correction[i];
        }
    }
}