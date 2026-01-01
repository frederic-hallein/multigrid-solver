#pragma once

#include "../common/smoother_param.hpp"
#include "../common/type_alias.hpp"
#include "../common/norm.hpp"
#include "../multigrid/cartesian_1d/smoother.hpp"
#include "../multigrid/cartesian_1d/cycle.hpp"

struct Config {
    unsigned int sub_int;
    unsigned int num_iter;
    double tolerance;
    SmootherParam smoother_param;
    Smoother smoother;
    double omega;
    Cycle cycle;
    Norm norm;
};

