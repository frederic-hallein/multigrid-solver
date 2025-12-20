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
    jacobi(A, x, b, K_max, 1e-3);


    return 0;
}