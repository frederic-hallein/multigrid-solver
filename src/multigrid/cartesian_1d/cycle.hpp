#pragma once

#include <vector>

#include "../../logger.hpp"
#include "../../common/type_alias.hpp"
#include "../../common/smoother_param.hpp"

#include "operations.hpp"
namespace multigrid::cartesian_1d::cycle {
    /*
    V(grids, 0, ...)
      └─> V(grids, 1, ...)
            └─> V(grids, 2, ...)
                  └─> V(grids, 3, ...)  // coarsest, direct solve, return
                  <-- prolongate, correct, post-smooth (level 2)
            <-- prolongate, correct, post-smooth (level 1)
      <-- prolongate, correct, post-smooth (level 0)
    */
    void V(
        std::vector<Grid>& grids,
        std::size_t level,
        double h,
        double sigma,
        double omega,
        const Smoother& smoother,
        const SmootherParam& smoother_param
    );
}