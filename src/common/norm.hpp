#pragma once

#include <vector>
#include <cmath>
#include <numeric>

namespace norm {
    inline double Lp(const std::vector<double>& v, double p) {
        double sum = 0.0;
        for (double x : v) {
            sum += std::pow(std::abs(x), p);
        }

        return std::pow(sum, 1.0 / p);
    }

    inline double L2(const std::vector<double>& v) {
        return Lp(v, 2.0);
    }

    inline double Linf(const std::vector<double>& v) {
        return std::abs(*std::max_element(v.begin(), v.end(), [](double a, double b) {
            return std::abs(a) < std::abs(b);
        }));
    }
}