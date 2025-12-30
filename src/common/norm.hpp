#pragma once

#include <vector>
#include <cmath>
#include <numeric>

inline double L2(const std::vector<double>& v) {
    return std::sqrt(std::inner_product(v.begin(), v.end(), v.begin(), 0.0));
}
