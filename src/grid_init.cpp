#include "grid_init.hpp"

std::vector<Grid> initialize_grids(
    Func1D rhs_func,
    Func1D u_guess,
    Domain1D dom,
    BoundaryCond1D bc,
    unsigned int sub_int
)
{
    logger::info("Initializing grids for 1D problem.");

    std::vector<Grid> grids;
    bool is_finest = true;
    unsigned int sub_int_current_grid = sub_int;
    while (sub_int_current_grid >= 2) {
        unsigned int n = sub_int_current_grid + 1;
        double h_level = (dom.x_max - dom.x_min) / sub_int_current_grid;
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

        grids.emplace_back(Grid{v, f});

        logger::info(
            "Created grid (level {}): v.size() = {}, f.size() = {}",
            grids.size() - 1, v.size(), f.size()
        );

        if (n == 3) break;
        sub_int_current_grid /= 2;
    }

    return grids;
}

std::vector<Grid> initialize_grids(
    Func2D rhs_func,
    Func2D u_guess,
    Domain2D dom,
    BoundaryCond2D bc,
    unsigned int sub_int
)
{
    logger::info("Initializing grids for 2D problem.");

    std::vector<Grid> grids;
    bool is_finest = true;
    unsigned int sub_int_current_grid = sub_int;
    while (sub_int_current_grid >= 2) {
        // TODO
    }

    return grids;
}