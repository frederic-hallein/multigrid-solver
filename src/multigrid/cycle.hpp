#pragma once


#include "../common/type_alias.hpp"
#include "../common/smoother_param.hpp"
#include "grid.hpp"

namespace multigrid::dim1 {
/*
v_cycle(grids, 0, ...)
    └─> V(grids, 1, ...)
        └─> V(grids, 2, ...)
                └─> V(grids, 3, ...)  // coarsest, direct solve, return
                <-- prolongate, correct, post-smooth (level 2)
        <-- prolongate, correct, post-smooth (level 1)
    <-- prolongate, correct, post-smooth (level 0)
*/
void v_cycle(
    std::vector<Grid1D>& grids,
    std::size_t level,
    double h,
    double sigma,
    double omega,
    const Smoother& smoother,
    const SmootherParam& smoother_param
);

/*
TODO
    */
void f_cycle(
    std::vector<Grid1D>& grids,
    std::size_t level,
    double h,
    double sigma,
    double omega,
    const Smoother& smoother,
    const SmootherParam& smoother_param
);

/*
TODO
    */
void w_cycle(
    std::vector<Grid1D>& grids,
    std::size_t level,
    double h,
    double sigma,
    double omega,
    const Smoother& smoother,
    const SmootherParam& smoother_param
);
}

namespace multigrid::dim2 {
void v_cycle(
    std::vector<Grid2D>& grids,
    std::size_t level,
    double h_x,
    double h_y,
    double sigma,
    double omega,
    const Smoother& smoother,
    const SmootherParam& smoother_param
);
}