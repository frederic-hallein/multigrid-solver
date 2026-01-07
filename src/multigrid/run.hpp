#pragma once

#include <optional>
#include <vector>
#include <chrono>

#include "../config.hpp"
#include "../common/logger.hpp"
#include "../common/io.hpp"
#include "../common/type_alias.hpp"
#include "../common/boundary_condition.hpp"
#include "../common/domain.hpp"
#include "../common/smoother_param.hpp"
#include "../common/norm.hpp"

#include "pde.hpp"
#include "smoother.hpp"
#include "cycle.hpp"
#include "init_grids.hpp"
#include "operations.hpp"

namespace multigrid {
    struct MG1DResults {
        std::vector<std::vector<double>> v;
        std::vector<double> residual_norm;
    };

    std::optional<MG1DResults> run(
        const ModHelmholtz& pde,
        const Config& config,
        const std::optional<Func1D>& u_exact = std::nullopt,
        const Func1D& u_guess = [](double) { return 0.0; }
    );
}