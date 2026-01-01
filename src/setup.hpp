#pragma once

#include <string>
#include <fstream>
#include <yaml-cpp/yaml.h>

#include "logger.hpp"
#include "config.hpp"

inline Smoother string_to_smoother(const std::string& s) {
    if (s == "J") return multigrid::cartesian_1d::jacobi;
    if (s == "GS") return multigrid::cartesian_1d::gauss_seidel;
    if (s == "RBGS") return multigrid::cartesian_1d::red_black_gauss_seidel;
    logger::warning("Unknown smoother '{}', using default: JACOBI.", s);
    return multigrid::cartesian_1d::jacobi;
}

inline Cycle string_to_cycle(const std::string& s) {
    if (s == "V") return multigrid::cartesian_1d::v_cycle;
    if (s == "W") return multigrid::cartesian_1d::w_cycle;
    if (s == "F") return multigrid::cartesian_1d::f_cycle;
    logger::warning("Unknown cycle '{}', using default: V.", s);
    return multigrid::cartesian_1d::v_cycle;
}

inline Norm string_to_norm(const std::string& s) {
    if (s == "L2") return norm::L2;
    if (s == "LINF") return norm::Linf;
    logger::warning("Unknown norm '{}', using default: L2.", s);
    return norm::L2;
}

inline Config load_config(const std::string& filepath) {
    Config config;
    try {
        YAML::Node yaml = YAML::LoadFile(filepath);

        if (!yaml["grid"] || !yaml["grid"]["sub_intervals"]) {
            throw std::runtime_error("Missing parameter: grid.sub_intervals");
        }
        if (!yaml["solver"] || !yaml["solver"]["num_iterations"]) {
            throw std::runtime_error("Missing parameter: solver.num_iterations");
        }
        if (!yaml["solver"] || !yaml["solver"]["tolerance"]) {
            throw std::runtime_error("Missing parameter: solver.tolerance");
        }
        if (!yaml["solver"] || !yaml["solver"]["smoother"]) {
            throw std::runtime_error("Missing parameter: solver.smoother");
        }
        if (!yaml["solver"] || !yaml["solver"]["cycle"]) {
            throw std::runtime_error("Missing parameter: solver.cycle");
        }
        if (!yaml["solver"] || !yaml["solver"]["norm"]) {
            throw std::runtime_error("Missing parameter: solver.norm");
        }
        if (!yaml["solver"] || !yaml["solver"]["omega"]) {
            throw std::runtime_error("Missing parameter: solver.omega");
        }
        if (!yaml["smoother"] || !yaml["smoother"]["pre_iterations"]) {
            throw std::runtime_error("Missing parameter: smoother.pre_iterations");
        }
        if (!yaml["smoother"] || !yaml["smoother"]["post_iterations"]) {
            throw std::runtime_error("Missing parameter: smoother.post_iterations");
        }

        config.sub_int = yaml["grid"]["sub_intervals"].as<unsigned int>();
        config.num_iter = yaml["solver"]["num_iterations"].as<unsigned int>();
        config.tolerance = yaml["solver"]["tolerance"].as<double>();
        config.smoother = string_to_smoother(yaml["solver"]["smoother"].as<std::string>());
        config.cycle = string_to_cycle(yaml["solver"]["cycle"].as<std::string>());
        config.norm = string_to_norm(yaml["solver"]["norm"].as<std::string>());
        config.omega = yaml["solver"]["omega"].as<double>();
        config.smoother_param.nu_1 = yaml["smoother"]["pre_iterations"].as<unsigned int>();
        config.smoother_param.nu_2 = yaml["smoother"]["post_iterations"].as<unsigned int>();
    } catch (const YAML::Exception& e) {
        throw std::runtime_error("Failed to load config file " + filepath + ": " + e.what());
    }

    return config;
}