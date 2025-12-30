#pragma once

#include <functional>
#include <vector>

#include "smoother_param.hpp"
#include "../multigrid/cartesian_1d/grid.hpp"

using Func1D = std::function<double(double)>;
using Func2D = std::function<double(double, double)>;
using Func3D = std::function<double(double, double, double)>;

using Smoother = std::function<void(
    std::vector<double>&,
    const std::vector<double>&,
    double,
    double,
    double
)>;

using Cycle = std::function<void(
    std::vector<Grid>&,
    double,
    double,
    double,
    const Smoother&,
    const SmootherParam&
)>;