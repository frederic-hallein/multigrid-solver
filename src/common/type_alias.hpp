#pragma once

#include <functional>
#include <vector>

#include "smoother_param.hpp"
#include "../multigrid/grid.hpp"

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

template<typename Grid>
using Cycle = std::function<void(
    std::vector<Grid>&,
    std::size_t,
    double,
    double,
    double,
    const Smoother&,
    const SmootherParam&
)>;