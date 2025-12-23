#pragma once
#include <vector>
#include <functional>
#include "smoother.hpp"

using Func1D = std::function<double(double)>;
using Func2D = std::function<double(double, double)>;
using BoundaryCond1D = std::function<double(double)>;
using BoundaryCond2D = std::function<double(double, double)>;

enum class CycleType { V, W, F };
// TODO : add enum for type of BC

struct Grid {
    std::vector<double> v;
    std::vector<double> f;
};

class MG {
public:
    MG(
        Func1D rhs_func_1d,
        BoundaryCond1D boundary,
        double x_min, double x_max,
        double alpha
    );

    MG(
        Func2D rhs_func_2d,
        BoundaryCond2D boundary,
        double x_min, double x_max,
        double y_min, double y_max,
        double alpha
    );

    void run(
        unsigned int n,
        smoother::SmootherType smoother_type,
        CycleType cycle_type,
        unsigned int nu_1,
        unsigned int nu_2,
        Func1D u_guess
    );

    void run(
        unsigned int n,
        smoother::SmootherType smoother_type,
        CycleType cycle_type,
        unsigned int nu_1,
        unsigned int nu_2,
        Func2D u_guess
    );

    friend class multigrid_initialize_grids_1d_Test;
    friend class multigrid_initialize_grids_2d_Test;

private:
    Func1D rhs_func_1d;
    Func2D rhs_func_2d;
    BoundaryCond1D boundary_1d_;
    BoundaryCond2D boundary_2d_;
    double x_min_, x_max_, y_min_, y_max_;
    double alpha_;
    std::function<void(std::vector<double>&, const std::vector<double>&, double, unsigned int, int)> smooth_;
    std::vector<Grid> grids_;

    void initialize_grids_1d(
        unsigned int coarse_level,
        Func1D u_guess
    );
    void initialize_grids_2d(
        unsigned int coarse_level,
        Func2D u_guess
    );
    void set_smoother(smoother::SmootherType smoother_type);
    std::vector<double> v_cycle(
        unsigned int nu_1,
        unsigned int nu_2
    );
};