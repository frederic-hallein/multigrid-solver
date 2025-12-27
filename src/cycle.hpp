#pragma once

#include <vector>

#include "logger.hpp"
#include "type_alias.hpp"
#include "smoother_param.hpp"
#include "multigrid_operations.hpp"

namespace cycle {
    /*
    TODO : update docstring format

    v_cycle(grids, 0)
        └─> v_cycle(grids, 1)
            └─> v_cycle(grids, 2)
                └─> v_cycle(grids, 3)  // coarsest, direct solve, return
                <-- prolongate, correct, post-smooth (level 2)
            <-- prolongate, correct, post-smooth (level 1)
        <-- prolongate, correct, post-smooth (level 0)
    */
    void v_cycle(
        std::vector<Grid>& grids,
        size_t level,
        double h,
        double sigma,
        double omega,
        const Smoother& smoother,
        const SmootherParam& smoother_param
    );

    // std::vector<double> w_cycle(
    // );
}