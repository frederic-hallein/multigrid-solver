#include "multigrid.hpp"

namespace multigrid {
    std::vector<double> run_helmholtz_cartesian_1d(
        Func1D rhs_f,
        BoundaryCond1D bc,
        double sigma,
        Domain1D dom,
        unsigned int sub_int,
        Func1D u_guess,
        SmootherParam smoother_param,
        Smoother smoother,
        Cycle cycl
    )
    {
        if (sub_int % 2 != 0) {
            // TODO : print error
            return {};
        }

        return {};
    }

    std::vector<double> run_helmholtz_cartesian_2d(
        Func2D rhs_f,
        BoundaryCond2D bc,
        double sigma,
        Domain2D dom,
        unsigned int sub_int,
        Func2D u_guess,
        SmootherParam smoother_param,
        Smoother smoother,
        Cycle cycle
    )
    {
        if (sub_int % 2 != 0) {
            // TODO : print error
            return {};
        }

        return {};
    }
}