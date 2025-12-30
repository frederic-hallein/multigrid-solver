#pragma once

#include <vector>

#include "logger.hpp"
#include "type_alias.hpp"
#include "smoother_param.hpp"
#include "multigrid_operations.hpp"

namespace cycle {
    /*
    V(grids, ...)
      └─> v_cycle_recursive(grids, 0, ...)
            └─> v_cycle_recursive(grids, 1, ...)
                  └─> v_cycle_recursive(grids, 2, ...)
                        └─> v_cycle_recursive(grids, 3, ...)  // coarsest, direct solve, return
                        <-- prolongate, correct, post-smooth (level 2)
                  <-- prolongate, correct, post-smooth (level 1)
            <-- prolongate, correct, post-smooth (level 0)
    */
    void V(
        std::vector<Grid>& grids,
        double h,
        double sigma,
        double omega,
        const Smoother& smoother,
        const SmootherParam& smoother_param
    );
}