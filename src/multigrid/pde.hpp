#pragma once

#include "../common/type_alias.hpp"
#include "../common/domain.hpp"
#include "../common/boundary_condition.hpp"

struct ModHelmholtz1D {
    double sigma;
    Domain1D dom;
    BoundaryCond1D bc;
    Func1D f;
};

struct ModHelmholtz2D {
    double sigma;
    Domain2D dom;
    BoundaryCond2D bc;
    Func2D f;
};
