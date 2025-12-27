#include "multigrid.hpp"

namespace multigrid {
    std::vector<double> run_helmholtz_cartesian_1d(
        Func1D rhs_f,
        BoundaryCond1D bc,
        double sigma,
        Domain1D dom,
        unsigned int sub_int,
        Func1D u_guess,
        const SmootherParam& smoother_param,
        const Smoother& smoother,
        double omega,
        Cycle cycle
    )
    {
        if (sub_int % 2 != 0) {
            logger::info("Sub intervals are not a multiple of 2.");
            return {};
        }

        std::vector<Grid> grids = initialize_grids(rhs_f, u_guess, dom, bc, sub_int);

        double h = (dom.x_max - dom.x_min) / sub_int;
        cycle(grids, 0, h, sigma, omega, smoother, smoother_param);

        return grids[0].v;
    }

    // std::vector<double> run_helmholtz_cartesian_2d(
    //     Func2D rhs_f,
    //     BoundaryCond2D bc,
    //     double sigma,
    //     Domain2D dom,
    //     unsigned int sub_int,
    //     Func2D u_guess,
    //     SmootherParam smoother_param,
    //     Smoother smoother,
    //     Cycle cycle
    // )
    // {
    //     if (sub_int % 2 != 0) {
    //         logger::info("Sub intervals are not a multiple of 2.");
    //         return {};
    //     }

    //     return {};
    // }
}