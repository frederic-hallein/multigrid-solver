#pragma once
#include <vector>
#include <functional>
#include "common.hpp"
#include "stencils.hpp"

namespace smoother {
    enum class SmootherType { J, WJ, GS, RBGS };

    void jacobi(
        std::vector<double>& v,
        const std::vector<double>& f,
        unsigned int n,
        double h
    );
}