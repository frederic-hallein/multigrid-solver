#pragma once

#include <vector>
#include <chrono>

#include "../../logger.hpp"
#include "../../common/io.hpp"
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
    struct MG1DResults {
        std::vector<std::vector<double>> v;
        std::vector<unsigned int> iter;
        std::vector<double> residual_norm;
    };

    MG1DResults run(
        const Func1D& rhs_f,
        const BoundaryCond1D& bc,
        double sigma,
        const Domain1D& domain,
        unsigned int sub_int,
        unsigned int num_iterations,
        double tolerance = 1e-6,
        const Func1D& u_guess = [](double) { return 0.0; },
        const SmootherParam& smoother_param = SmootherParam(),
        const Smoother& smoother = jacobi,
        double omega = 1.0,
        const Cycle& cycle = V
    );
}