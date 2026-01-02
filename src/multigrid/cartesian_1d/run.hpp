#pragma once

#include <optional>
#include <vector>
#include <chrono>

#include "../../config.hpp"
#include "../../common/logger.hpp"
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
        std::vector<double> residual_norm;
    };

    std::optional<MG1DResults> run(
        const Func1D& rhs_f,
        double sigma,
        Domain1D dom,
        const BoundaryCond1D& bc,
        Config config,
        const Func1D& u_guess = [](double) { return 0.0; },
        const std::optional<Func1D>& u_exact = std::nullopt
    );
}