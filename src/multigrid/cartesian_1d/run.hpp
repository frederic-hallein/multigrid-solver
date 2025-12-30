#pragma once

#include <vector>

#include "../../logger.hpp"
#include "../../common/type_alias.hpp"
#include "../../common/boundary_condition.hpp"
#include "../../common/domain.hpp"
#include "../../common/smoother_param.hpp"
#include "../../common/norm.hpp"

#include "smoother.hpp"
#include "cycle.hpp"
#include "init_grids.hpp"
#include "operations.hpp"

namespace multigrid::cartesian_1d {
    std::vector<double> run(
        Func1D rhs_f,
        BoundaryCond1D bc,
        double sigma,
        Domain1D domain,
        unsigned int sub_int,
        unsigned int num_iterations,
        double tolerance = 1e-6,
        Func1D u_guess = [](double) { return 0.0; },
        const SmootherParam& smoother_param = SmootherParam(),
        const Smoother& smoother = jacobi,
        double omega = 2.0 / 3.0,
        Cycle cycle = V
    );
}