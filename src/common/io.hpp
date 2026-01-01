#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

#include "type_alias.hpp"
#include "domain.hpp"
#include "norm.hpp"

inline void save_solutions_csv(
    const std::string& filename,
    const std::vector<std::vector<double>>& v
)
{
    std::filesystem::create_directories(std::filesystem::path(filename).parent_path());
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
    const Norm& norm
)
{
    std::filesystem::create_directories(std::filesystem::path(filename).parent_path());
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