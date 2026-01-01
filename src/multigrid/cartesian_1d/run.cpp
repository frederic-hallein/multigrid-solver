#include "run.hpp"

namespace multigrid::cartesian_1d {
    std::optional<MG1DResults> run(
        const Func1D& rhs_f,
        double sigma,
        Domain1D dom,
        const BoundaryCond1D& bc,
        Config config,
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
        std::vector<Grid> grids = init_grids(rhs_f, u_guess, dom, bc, config.sub_int);
        double h = (dom.x_max - dom.x_min) / config.sub_int;

        logger::info("Running multigrid...");
        auto start = std::chrono::high_resolution_clock::now();
        for (unsigned int iter = 0; iter < config.num_iter; ++iter) {
            config.cycle(grids, 0, h, sigma, config.omega, config.smoother, config.smoother_param);

            auto r = compute_residual(grids[0].v, grids[0].f, h, sigma);
            double residual_norm = config.norm(r);

            results.v.push_back(grids[0].v);
            results.residual_norm.push_back(residual_norm);

            if (residual_norm < config.tolerance) {
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                logger::info("Converged at iteration step ({}/{}) with tolerance = {}", iter, config.num_iter, config.tolerance);
                logger::info("Elapsed time: {} seconds", elapsed.count());

                save_solutions_csv("../data/solutions.csv", results.v);
                // TODO : handle u_exact by setting it optional. If not specified, do not calculate error norm
                // save_convergence_history_csv("../data/convergence_history.csv", results.residual_norm, results.v, dom, config.sub_int, u_exact, config.norm);
                return results;
            }
        }

        logger::error("Did not converge within the maximum number of iterations ({}).", config.num_iter);
        return std::nullopt;
    }
}