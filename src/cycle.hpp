#pragma once

#include <vector>

#include "smoother_param.hpp"

namespace cycle {
    std::vector<double> v_cycle(
        std::vector<double>& v,
        const std::vector<double>& f,
        double h,
        const SmootherParam& smoother_param
    );

    std::vector<double> w_cycle(
        std::vector<double>& v,
        const std::vector<double>& f,
        double h,
        const SmootherParam& smoother_param
    );
}