#include <iostream>

#include "logger.hpp"
#include "solver.hpp"

int main() {
    std::vector<std::vector<double>> A = {
        {2, 1},
        {5, 7}
    };
    std::vector<double> b = {11, 13};
    std::vector<double> x = {1, 1};

    int K_max = 25;
    solver::jacobi(A, x, b, K_max, 1e-3);


    // std::vector<std::vector<double>> A = {
    //     {16, 3},
    //     {7, -11}
    // };
    // std::vector<double> b = {11, 13};
    // std::vector<double> x = {1, 1};

    // int K_max = 7;
    // solver::gauss_seidel(A, x, b, K_max, 1e-2);


    return 0;
}