#pragma once
#include <vector>

namespace cycle {
    std::vector<double> v_cycle(
        std::vector<double>& v,
        const std::vector<double>& f,
        double h
    );

    std::vector<double> W_cycle(
        std::vector<double>& v,
        const std::vector<double>& f,
        double h
    );
}