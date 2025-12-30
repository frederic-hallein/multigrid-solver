#pragma once

#include "logger.hpp"
#include "type_alias.hpp"
#include "boundary_condition.hpp"
#include "domain.hpp"
#include "smoother_param.hpp"
#include "smoother.hpp"
#include "cycle.hpp"
#include "grid_init.hpp"
#include "multigrid_operations.hpp"
#include "norm.hpp"

namespace multigrid {
    std::vector<double> run_helmholtz_cartesian_1d(
        Func1D rhs_f,
        BoundaryCond1D bc,
        double sigma,
        Domain1D domain,
        unsigned int sub_int,
        unsigned int num_iterations,
        double tolerance = 1e-10,
        Func1D u_guess = [](double) { return 0.0; },
        const SmootherParam& smoother_param = SmootherParam(),
        const Smoother& smoother = smoother_1d::jacobi,
        double omega = 2.0 / 3.0,
        Cycle cycle = cycle::V
    );
}