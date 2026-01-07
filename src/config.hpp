#pragma once

#include <unordered_map>
#include <string>
#include <yaml-cpp/yaml.h>

#include "../common/smoother_param.hpp"
#include "../common/type_alias.hpp"
#include "../common/norm.hpp"
#include "../multigrid/smoother.hpp"
#include "../multigrid/cycle.hpp"
#include "common/logger.hpp"

const std::string CONFIG_PATH = "../data/config.yaml";

class Config {
public:
    unsigned int dim;
    unsigned int sub_int;
    unsigned int num_iter;
    double tolerance;
    SmootherParam smoother_param;
    std::pair<std::string, Smoother> smoother;
    double omega;
    std::pair<std::string, Cycle<Grid1D>> cycle; // std::pair<std::string, std::variant<Cycle<Grid1D>, Cycle<Grid2D>>> cycle;
    std::pair<std::string, Norm> norm;

    Config() {
        load_config(CONFIG_PATH);
        log_config_summary();
    }

    void log_config_summary() const {
        logger::info("---- Configuration Summary ----");
        logger::info("- sub intervals: {}", sub_int);
        logger::info("- num iterations: {}", num_iter);
        logger::info("- tolerance: {}", tolerance);
        logger::info("- cycle: {}({}, {})", cycle.first, smoother_param.nu_1, smoother_param.nu_2);
        logger::info("- smoother: {} (omega = {})", smoother.first, omega);
        logger::info("- norm: {}", norm.first);
        logger::info("-------------------------------\n");
    }

private:
    std::unordered_map<std::string, Smoother> smoother_map{
        {"J"   , multigrid::cart_1d::jacobi},
        {"GS"  , multigrid::cart_1d::gauss_seidel},
        {"RBGS", multigrid::cart_1d::red_black_gauss_seidel}
    };

    std::unordered_map<std::string, Cycle<Grid1D>> cycle_map_1d{
        {"V", multigrid::v_cycle},
        {"F", multigrid::f_cycle},
        {"W", multigrid::w_cycle}
    };

    std::unordered_map<std::string, Cycle<Grid2D>> cycle_map_2d{
        // {"V", multigrid::v_cycle},
        // {"F", multigrid::f_cycle},
        // {"W", multigrid::w_cycle}
    };

    std::unordered_map<std::string, Norm> norm_map{
        {"L2"  , norm::L2},
        {"LINF", norm::Linf}
    };

    void load_config(const std::string& filepath) {
        try {
            YAML::Node yaml = YAML::LoadFile(filepath);

            if (!yaml["grid"] || !yaml["grid"]["dim"]) {
                throw std::runtime_error("Missing parameter: grid.dim");
            }
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

            dim = yaml["grid"]["dim"].as<unsigned int>();
            sub_int = yaml["grid"]["sub_intervals"].as<unsigned int>();
            num_iter = yaml["solver"]["num_iterations"].as<unsigned int>();
            tolerance = yaml["solver"]["tolerance"].as<double>();

            std::string smoother_key = yaml["solver"]["smoother"].as<std::string>();
            auto s_it = smoother_map.find(smoother_key);
            if (s_it != smoother_map.end()) {
                smoother = std::make_pair(smoother_key, s_it->second);
            } else {
                logger::warning("Unknown smoother '{}', using default: J.", smoother_key);
                smoother = std::make_pair("J", smoother_map.at("J"));
            }

            std::string cycle_key = yaml["solver"]["cycle"].as<std::string>();
            if (dim == 1) {
                auto c_it = cycle_map_1d.find(cycle_key);
                if (c_it != cycle_map_1d.end()) {
                    cycle = std::make_pair(cycle_key, c_it->second);
                } else {
                    logger::warning("Unknown cycle '{}', using default: V.", cycle_key);
                    cycle = std::make_pair("V", cycle_map_1d.at("V"));
                }
            // } else if (dim == 2) {
            //     auto c_it = cycle_map_2d.find(cycle_key);
            //     if (c_it != cycle_map_2d.end()) {
            //         cycle = std::make_pair(cycle_key, c_it->second);
            //     } else {
            //         logger::warning("Unknown cycle '{}', using default: V.", cycle_key);
            //         // cycle = std::make_pair("V", cycle_map_2d.at("V"));
            //     }
            // } else {
            //     throw std::runtime_error("Unsupported grid dimension: " + std::to_string(dim));
            }

            std::string norm_key = yaml["solver"]["norm"].as<std::string>();
            auto n_it = norm_map.find(norm_key);
            if (n_it != norm_map.end()) {
                norm = std::make_pair(norm_key, n_it->second);
            } else {
                logger::warning("Unknown norm '{}', using default: L2.", norm_key);
                norm = std::make_pair("L2", norm_map.at("L2"));
            }

            omega = yaml["solver"]["omega"].as<double>();
            smoother_param.nu_1 = yaml["smoother"]["pre_iterations"].as<unsigned int>();
            smoother_param.nu_2 = yaml["smoother"]["post_iterations"].as<unsigned int>();
        } catch (const YAML::Exception& e) {
            throw std::runtime_error("Failed to load config file " + filepath + ": " + e.what());
        }
    }
};