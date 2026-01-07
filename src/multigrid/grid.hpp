#pragma once

struct Grid1D {
    std::vector<double> v;
    std::vector<double> f;
};

struct Grid2D {
    std::vector<std::vector<double>> v;
    std::vector<std::vector<double>> f;
};