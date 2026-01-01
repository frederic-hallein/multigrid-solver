#pragma once

#include <string>
#include <fstream>
#include <yaml-cpp/yaml.h>

#include "common/logger.hpp"
#include "config.hpp"

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

        std::string smoother_key = yaml["solver"]["smoother"].as<std::string>();
        auto s_it = smoother_map.find(smoother_key);
        if (s_it != smoother_map.end()) {
            config.smoother_name = smoother_key;
            config.smoother = s_it->second;
        } else {
            logger::warning("Unknown smoother '{}', using default: J.", smoother_key);
            config.smoother_name = "J";
            config.smoother = smoother_map.at("J");
        }

        std::string cycle_key = yaml["solver"]["cycle"].as<std::string>();
        auto c_it = cycle_map.find(cycle_key);
        if (c_it != cycle_map.end()) {
            config.cycle_name = cycle_key;
            config.cycle = c_it->second;
        } else {
            logger::warning("Unknown cycle '{}', using default: V.", cycle_key);
            config.cycle_name = "V";
            config.cycle = cycle_map.at("V");
        }

        std::string norm_key = yaml["solver"]["norm"].as<std::string>();
        auto n_it = norm_map.find(norm_key);
        if (n_it != norm_map.end()) {
            config.norm_name = norm_key;
            config.norm = n_it->second;
        } else {
            logger::warning("Unknown norm '{}', using default: L2.", norm_key);
            config.norm_name = "L2";
            config.norm = norm_map.at("L2");
        }

        config.omega = yaml["solver"]["omega"].as<double>();
        config.smoother_param.nu_1 = yaml["smoother"]["pre_iterations"].as<unsigned int>();
        config.smoother_param.nu_2 = yaml["smoother"]["post_iterations"].as<unsigned int>();
    } catch (const YAML::Exception& e) {
        throw std::runtime_error("Failed to load config file " + filepath + ": " + e.what());
    }

    return config;
}