#pragma once
#include <functional>

#include "smoother_param.hpp"

using Func1D = std::function<double(double)>;
using Func2D = std::function<double(double, double)>;
using Func3D = std::function<double(double, double, double)>;

using Smoother = std::function<void(std::vector<double>&, const std::vector<double>&, unsigned int)>;
using Cycle = std::function<void(std::vector<double>&, const std::vector<double>&, double)>;