#pragma once

#include "type_alias.hpp"

struct BoundaryCond1D {
    Func1D left, right;
};

struct BoundaryCond2D {
    Func2D left, right;
    Func2D down, up;
};

struct BoundaryCond3D {
    Func2D left, right;
    Func2D down, up;
    Func2D forw, back;
};
