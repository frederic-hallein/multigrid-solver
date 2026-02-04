#pragma once

#include <optional>
#include <vector>

#include "../config.hpp"
#include "../common/type_alias.hpp"

#include "pde.hpp"
namespace multigrid {
    struct MG1DResults {
        std::vector<std::vector<double>> v;
        std::vector<double> residual_norm;
    };

    struct MG2DResults {
        std::vector<std::vector<double>> v;
        std::vector<double> residual_norm;
    };

    std::optional<MG1DResults> run(
        const ModHelmholtz1D& pde,
        const Config& config,
        const std::optional<Func1D>& u_exact = std::nullopt,
        Func1D u_guess = [](double) { return 0.0; }
    );

    std::optional<MG2DResults> run(
        const ModHelmholtz2D& pde,
        const Config& config,
        const std::optional<Func2D>& u_exact = std::nullopt,
        Func2D u_guess = [](double, double) { return 0.0; }
    );
}