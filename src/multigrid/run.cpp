#include "run.hpp"

namespace multigrid {
    std::optional<MG1DResults> run(
        const ModHelmholtz& pde,
        const Config& config,
        const std::optional<Func1D>& u_exact,
        const Func1D& u_guess
    )
    {
        if (config.sub_int == 0) {
            logger::error("Sub intervals cannot be 0.");
            return std::nullopt;
        }

        if (config.sub_int % 2 != 0) {
            logger::error("Sub intervals are not a multiple of 2.");
            return std::nullopt;
        }

        MG1DResults results;
        std::vector<Grid1D> grids = init_grids(pde.f, u_guess, pde.dom, pde.bc, config.sub_int);
        double h = (pde.dom.x_max - pde.dom.x_min) / config.sub_int;

        logger::info("Running multigrid...");
        auto start = std::chrono::high_resolution_clock::now();
        for (unsigned int iter = 1; iter <= config.num_iter; ++iter) {
            config.cycle.second(grids, 0, h, pde.sigma, config.omega, config.smoother.second, config.smoother_param);

            auto r = compute_residual(grids[0].v, grids[0].f, h, pde.sigma);
            double residual_norm = config.norm.second(r);

            results.v.push_back(grids[0].v);
            results.residual_norm.push_back(residual_norm);

            if (residual_norm < config.tolerance) {
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                logger::info("Converged at iteration step ({}/{})", iter, config.num_iter);
                logger::info("Elapsed time: {} seconds", elapsed.count());

                save_grid_points("../data/grid_points.csv", pde.dom, h, config.sub_int);
                save_solutions_csv("../data/solutions.csv", results.v);
                save_convergence_history_csv("../data/convergence_history.csv", results.residual_norm, results.v, pde.dom, config.sub_int, config.norm.second, u_exact);

                return results;
            }
        }

        logger::error("Did not converge within the maximum number of iterations ({}).", config.num_iter);
        return std::nullopt;
    }
}