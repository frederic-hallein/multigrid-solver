#pragma once

#include "../common/type_alias.hpp"
#include "../common/domain.hpp"
#include "../common/boundary_condition.hpp"

namespace multigrid {
    struct ModHelmholtz {
        double sigma;
        Domain1D dom;
        BoundaryCond1D bc;
        Func1D f;
    };
}