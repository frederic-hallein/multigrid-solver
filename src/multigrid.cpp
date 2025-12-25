#include "multigrid.hpp"

namespace multigrid {
    std::vector<double> run_helmholtz_1d(
        Func1D rhs_f,
        BoundaryCond1D bc,
        double alpha, // (>= 0)
        Domain1D domain,
        unsigned int sub_int,
        Func1D u_guess = [](double) { return 0.0; },
        SmootherParam smoother_param = SmootherParam(),
        Smoother smoother = smoother_1d::jacobi,
        Cycle cycle = cycle::v_cycle
    )
    {

    }

    std::vector<double> run_helmholtz_2d(
        Func2D rhs_f,
        BoundaryCond2D bc,
        double alpha, // (>= 0)
        Domain2D domain,
        unsigned int sub_int,
        Func2D u_guess = [](double, double) { return 0.0; },
        SmootherParam smoother_param = SmootherParam(),
        Smoother smoother = smoother_2d::jacobi,
        Cycle cycle = cycle::v_cycle
    )
    {

    }
}