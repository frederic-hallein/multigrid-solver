#pragma once

#include "../common/logger.hpp"
#include "../common/type_alias.hpp"
#include "../common/domain.hpp"
#include "../common/boundary_condition.hpp"
#include "grid.hpp"

namespace multigrid {
    std::vector<Grid1D> init_grids(
        Func1D rhs_func,
        Func1D u_guess,
        Domain1D dom,
        BoundaryCond1D bc,
        unsigned int sub_int
    );
}

// namespace multigrid::cartesian_2d {
//     std::vector<Grid2D> init_grids(
//         Func2D rhs_func,
//         Func2D u_guess,
//         Domain2D dom,
//         BoundaryCond2D bc,
//         unsigned int sub_int
//     );
// }