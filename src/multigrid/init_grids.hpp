#pragma once

#include "../common/type_alias.hpp"
#include "../common/domain.hpp"
#include "../common/boundary_condition.hpp"
#include "grid.hpp"

namespace multigrid::dim1 {
std::vector<Grid1D> init_grids(
    Func1D rhs_func,
    Func1D u_guess,
    const Domain1D& dom,
    const BoundaryCond1D& bc,
    unsigned int sub_int,
    double h
);
}
namespace multigrid::dim2 {
std::vector<Grid2D> init_grids(
    Func2D rhs_func,
    Func2D u_guess,
    const Domain2D& dom,
    const BoundaryCond2D& bc,
    unsigned int sub_int_x,
    unsigned int sub_int_y,
    double h_x,
    double h_y
);
}
