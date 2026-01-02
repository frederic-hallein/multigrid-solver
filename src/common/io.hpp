#pragma once

#include <vector>
#include <string>
#include <optional>
#include <fstream>
#include <filesystem>

#include "type_alias.hpp"
#include "domain.hpp"
#include "norm.hpp"

inline void save_grid_points(
    const std::string& filename,
    const Domain1D& dom,
    double h,
    unsigned int sub_int
)
{
    std::filesystem::create_directories(std::filesystem::path(filename).parent_path());
    std::ofstream file(filename);
    file << "x\n";

    for (unsigned int i = 0; i <= sub_int; ++i) {
        double x = dom.x_min + i * h;
        file << x << "\n";
    }
}

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
    const Norm& norm,
    const std::optional<Func1D>& u_exact
)
{
    std::filesystem::create_directories(std::filesystem::path(filename).parent_path());
    std::ofstream file(filename);

    if (u_exact) {
        file << "iter;residual_norm;error_norm\n";
    } else {
        file << "iter;residual_norm\n";
    }

    double h = (dom.x_max - dom.x_min) / sub_int;
    for (size_t k = 0; k < v.size(); ++k) {
        file << k+1 << ";" << residual_norm[k];

        if (u_exact) {
            std::vector<double> error(v[k].size());
            for (size_t i = 0; i < v[k].size(); ++i) {
                double x = dom.x_min + i * h;
                error[i] = v[k][i] - u_exact.value()(x);
            }
            double error_norm = norm(error);
            file << ";" << error_norm;
        }

        file << "\n";
    }
}