#pragma once

#include <functional>
#include <vector>

#include "../multigrid/grid.hpp"
#include "smoother_param.hpp"

using Func1D = std::function<double(double)>;
using Func2D = std::function<double(double, double)>;

using Norm = std::function<double(const std::vector<double>&)>;

using Smoother = std::function<void(
    std::vector<double>&,
    const std::vector<double>&,
    double,
    double,
    double
)>;

using Cycle1D = std::function<void(
    std::vector<Grid1D>&,
    std::size_t,
    double,
    double,
    double,
    const Smoother&,
    const SmootherParam&
)>;


using Cycle2D = std::function<void(
    std::vector<Grid2D>&,
    std::size_t,
    double,
    double,
    double,
    double,
    const Smoother&,
    const SmootherParam&
)>;