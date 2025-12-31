#pragma once

#include <vector>
#include <string>
#include <fstream>

#include "domain.hpp"

inline void save_params_yaml(
    const std::string& filename,
    Domain1D dom,
    double h,
    unsigned int sub_int,
    double tolerance,
    unsigned int num_iterations
)
{
    std::ofstream file(filename);
    file << "x_min: " << dom.x_min << '\n';
    file << "x_max: " << dom.x_max << '\n';
    file << "h: " << h << "\n";
    file << "sub_int: " << sub_int << "\n";
    file << "tolerance: " << tolerance << "\n";
    file << "num_iterations: " << num_iterations << "\n";
}

inline void save_solutions_csv(
    const std::string& filename,
    const std::vector<unsigned int>& iter,
    const std::vector<std::vector<double>>& v
) {
    std::ofstream file(filename);
    file << "iter;v\n";
    for (size_t k = 0; k < iter.size(); ++k) {
        file << iter[k] << ";";
        for (size_t i = 0; i < v[k].size(); ++i) {
            file << v[k][i];
            if (i + 1 < v[k].size()) file << ",";
        }
        file << "\n";
    }
}

inline void save_residuals_norm_csv(
    const std::string& filename,
    const std::vector<unsigned int>& iter,
    const std::vector<double>& residual_norm
)
{
    std::ofstream file(filename);
    file << "iter;residual_norm\n";
    for (size_t i = 0; i < iter.size(); ++i) {
        file << iter[i] << ";" << residual_norm[i] << "\n";
    }
}