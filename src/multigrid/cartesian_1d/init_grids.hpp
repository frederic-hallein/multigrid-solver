#pragma once

#include "../../common/logger.hpp"
#include "../../common/type_alias.hpp"
#include "../../common/domain.hpp"
#include "../../common/boundary_condition.hpp"
#include "grid.hpp"

namespace multigrid::cartesian_1d {
    std::vector<Grid> init_grids(
        Func1D rhs_func,
        Func1D u_guess,
        Domain1D dom,
        BoundaryCond1D bc,
        unsigned int sub_int
    );
}