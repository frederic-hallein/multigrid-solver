#pragma once

#include <unordered_map>

#include "../common/smoother_param.hpp"
#include "../common/type_alias.hpp"
#include "../common/norm.hpp"
#include "../multigrid/cartesian_1d/smoother.hpp"
#include "../multigrid/cartesian_1d/cycle.hpp"

inline std::unordered_map<std::string, Smoother> smoother_map{
    {"J", multigrid::cartesian_1d::jacobi},
    {"GS", multigrid::cartesian_1d::gauss_seidel},
    {"RBGS", multigrid::cartesian_1d::red_black_gauss_seidel}
};

inline std::unordered_map<std::string, Cycle> cycle_map{
    {"V", multigrid::cartesian_1d::v_cycle},
    {"F", multigrid::cartesian_1d::f_cycle},
    {"W", multigrid::cartesian_1d::w_cycle}
};
inline std::unordered_map<std::string, Norm> norm_map{
    {"L2", norm::L2},
    {"LINF", norm::Linf}
};

struct Config {
    unsigned int sub_int;
    unsigned int num_iter;
    double tolerance;
    SmootherParam smoother_param;
    std::string smoother_name;
    Smoother smoother;
    double omega;
    std::string cycle_name;
    Cycle cycle;
    std::string norm_name;
    Norm norm;
};

