#pragma once
#include "alias.hpp"

struct BoundaryCond1D {
    Func1D x_min, x_max;
};

struct BoundaryCond2D {
    Func2D x_min, x_max;
    Func2D y_min, y_max;
};

struct BoundaryCond2D {
    Func2D x_min, x_max;
    Func2D y_min, y_max;
    Func2D z_min, z_max;
};
