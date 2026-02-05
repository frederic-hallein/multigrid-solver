#include "../common/logger.hpp"
#include "init_grids.hpp"


namespace multigrid::dim1 {
std::vector<Grid1D> init_grids(
    Func1D rhs_func,
    Func1D u_guess,
    const Domain1D& dom,
    const BoundaryCond1D& bc,
    unsigned int sub_int,
    double h
)
{
    logger::info("Initializing 1D cartesian grid...");

    std::vector<Grid1D> grids;
    bool is_finest = true;
    unsigned int sub_int_current_grid = sub_int;
    double h_level = h;

    while (sub_int_current_grid >= 2) {
        unsigned int n = sub_int_current_grid + 1;
        std::vector<double> v(n, 0.0);
        std::vector<double> f(n, 0.0);

        if (is_finest) {
            for (unsigned int i = 0; i < n; ++i) {
                double x = dom.x_min + i * h_level;
                v[i] = u_guess(x);
                f[i] = rhs_func(x);
            }

            // set up boundary conditions
            v[0] = bc.left(dom.x_min);
            v[n-1] = bc.right(dom.x_max);

            is_finest = false;
        }

        grids.emplace_back(Grid1D{v, f});

        logger::debug(
            "Created grid (level {}): v.size() = {}, f.size() = {}",
            grids.size() - 1, v.size(), f.size()
        );

        if (n == 3) break;
        sub_int_current_grid /= 2;
        h_level *= 2.0;
    }

    logger::info("Created {} level multigrid", grids.size());
    return grids;
}
}

namespace multigrid::dim2 {
//   y ^
//     |
// n-1 o---o---o---...---o
//     |   |   |         |
//     o---o---o---...---o
//     |   |   |         |
//     .   .   .         .
//     |   |   |         |
//     o---o---o---...---o
//     |   |   |         |
// 0   o---o---o---...---o -> x
//
//     0   1   2        n-1
std::vector<Grid2D> init_grids(
    Func2D rhs_func,
    Func2D u_guess,
    const Domain2D& dom,
    const BoundaryCond2D& bc,
    unsigned int sub_int_x,
    unsigned int sub_int_y,
    double h_x,
    double h_y
)
{
    logger::info("Initializing 2D cartesian grid...");

    std::vector<Grid2D> grids;
    bool is_finest = true;
    unsigned int sub_int_x_current = sub_int_x;
    unsigned int sub_int_y_current = sub_int_y;
    double h_x_level = h_x;
    double h_y_level = h_y;

    while (sub_int_x_current >= 2 && sub_int_y_current >= 2) {
        unsigned int n_x = sub_int_x_current + 1;
        unsigned int n_y = sub_int_y_current + 1;
        std::vector<std::vector<double>> v(n_x, std::vector<double>(n_y, 0.0));
        std::vector<std::vector<double>> f(n_x, std::vector<double>(n_y, 0.0));

        if (is_finest) {
            for (unsigned int i = 0; i < n_x; ++i) {
                double x = dom.x_min + i * h_x_level;
                for (unsigned int j = 0; j < n_y; ++j) {
                    double y = dom.y_min + j * h_y_level;
                    v[i][j] = u_guess(x, y);
                    f[i][j] = rhs_func(x, y);
                }
            }

            // set up boundary conditions
            for (unsigned int i = 0; i < n_x; ++i) {
                double x = dom.x_min + i * h_x_level;
                v[i][0]      = bc.bottom(x, dom.y_min);
                v[i][n_y-1]  = bc.top(x, dom.y_max);
            }
            for (unsigned int j = 0; j < n_y; ++j) {
                double y = dom.y_min + j * h_y_level;
                v[0][j]      = bc.left(dom.x_min, y);
                v[n_x-1][j]  = bc.right(dom.x_max, y);
            }

            // take average at corners
            v[0][0]         = 0.5 * (bc.left(dom.x_min, dom.y_min)  + bc.bottom(dom.x_min, dom.y_min)); // bottom-left
            v[n_x-1][0]     = 0.5 * (bc.right(dom.x_max, dom.y_min) + bc.bottom(dom.x_max, dom.y_min)); // bottom-right
            v[0][n_y-1]     = 0.5 * (bc.left(dom.x_min, dom.y_max)  + bc.top(dom.x_min, dom.y_max));    // top-left
            v[n_x-1][n_y-1] = 0.5 * (bc.right(dom.x_max, dom.y_max) + bc.top(dom.x_max, dom.y_max));    // top-right

            is_finest = false;
        }

        grids.emplace_back(Grid2D{v, f});

        logger::debug(
            "Created grid (level {}): v.size() = {}, f.size() = {}",
            grids.size() - 1, v.size(), f.size()
        );

        if (n_x == 3 || n_y == 3) break;
        sub_int_x_current /= 2;
        sub_int_y_current /= 2;
        h_x_level *= 2.0;
        h_y_level *= 2.0;
    }

    logger::info("Created {} level multigrid", grids.size());
    return grids;
}
}
