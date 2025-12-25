#pragma once
#include <vector>

#include "stencils.hpp"

namespace smoother_1d {
    void jacobi(
        std::vector<double>& v,
        const std::vector<double>& f,
        unsigned int num_sweeps
    );

    void weighted_jacobi(
        std::vector<double>& v,
        const std::vector<double>& f,
        unsigned int num_sweeps
    );
    void gauss_seidel(
        std::vector<double>& v,
        const std::vector<double>& f,
        unsigned int num_sweeps
    );

    void red_black_gauss_seidel(
        std::vector<double>& v,
        const std::vector<double>& f,
        unsigned int num_sweeps
    );
}
namespace smoother_2d {
    void jacobi(
        std::vector<double>& v,
        const std::vector<double>& f,
        unsigned int num_sweeps
    );

    void weighted_jacobi(
        std::vector<double>& v,
        const std::vector<double>& f,
        unsigned int num_sweeps
    );
    void gauss_seidel(
        std::vector<double>& v,
        const std::vector<double>& f,
        unsigned int num_sweeps
    );

    void red_black_gauss_seidel(
        std::vector<double>& v,
        const std::vector<double>& f,
        unsigned int num_sweeps
    );
}