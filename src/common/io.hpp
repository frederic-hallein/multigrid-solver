#pragma once

#include <vector>
#include <string>
#include <fstream>

#include "type_alias.hpp"
#include "domain.hpp"
#include "norm.hpp"

inline void save_params_yaml(
    const std::string& filename,
    const Domain1D& dom,
    unsigned int sub_int
)
{
    std::ofstream file(filename);
    file << "domain:\n";
    file << "  x_min: " << dom.x_min << "\n";
    file << "  x_max: " << dom.x_max << "\n";
    file << "grid:\n";
    file << "  sub_intervals: " << sub_int << "\n";
}

inline void save_solutions_csv(
    const std::string& filename,
    const std::vector<std::vector<double>>& v
)
{
    std::ofstream file(filename);
    file << "iter;v\n";
    for (size_t k = 0; k < v.size(); ++k) {
        file << k << ";";
        for (size_t i = 0; i < v[k].size(); ++i) {
            file << v[k][i];
            if (i + 1 < v[k].size()) file << ",";
        }
        file << "\n";
    }
}

inline void save_convergence_history_csv(
    const std::string& filename,
    const std::vector<double>& residual_norm,
    const std::vector<std::vector<double>>& v,
    const Domain1D& dom,
    unsigned int sub_int,
    const Func1D& u_exact,
    const Norm& norm = L2
)
{
    std::ofstream file(filename);
    file << "iter;residual_norm;error_norm\n";

    double h = (dom.x_max - dom.x_min) / sub_int;

    for (size_t k = 0; k < v.size(); ++k) {
        std::vector<double> error(v[k].size());
        for (size_t i = 0; i < v[k].size(); ++i) {
            double x = dom.x_min + i * h;
            error[i] = v[k][i] - u_exact(x);
        }

        double error_norm = norm(error);

        file << k << ";" << residual_norm[k] << ";" << error_norm << "\n";
    }
}