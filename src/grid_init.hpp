#pragma once

#include "type_alias.hpp"
#include "logger.hpp"
#include "grid.hpp"
#include "domain.hpp"
#include "boundary_condition.hpp"

std::vector<Grid> initialize_grids(
    Func1D rhs_func,
    Func1D u_guess,
    Domain1D dom,
    BoundaryCond1D bc,
    unsigned int sub_int
);

std::vector<Grid> initialize_grids(
    Func2D rhs_func,
    Func2D u_guess,
    Domain2D dom,
    BoundaryCond2D bc,
    unsigned int sub_int
);