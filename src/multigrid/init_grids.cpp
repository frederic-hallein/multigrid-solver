#include "../common/logger.hpp"
#include "init_grids.hpp"

namespace multigrid {
    std::vector<Grid1D> init_grids(
        Func1D rhs_func,
        Func1D u_guess,
        Domain1D dom,
        BoundaryCond1D bc,
        unsigned int sub_int
    )
    {
        logger::info("Initializing 1D cartesian grid...");

        std::vector<Grid1D> grids;
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

            grids.emplace_back(Grid1D{v, f});

            logger::debug(
                "Created grid (level {}): v.size() = {}, f.size() = {}",
                grids.size() - 1, v.size(), f.size()
            );

            if (n == 3) break;
            sub_int_current_grid /= 2;
        }

        logger::info("Created {} level multigrid", grids.size());
        return grids;
    }
}

namespace multigrid::cartesian_2d {
    std::vector<Grid2D> init_grids(
        Func2D rhs_func,
        Func2D u_guess,
        Domain2D dom,
        BoundaryCond2D bc,
        unsigned int sub_int
    )
    {
        logger::info("Initializing 2D cartesian grid...");

        std::vector<Grid2D> grids;
        bool is_finest = true;
        unsigned int sub_int_current_grid = sub_int;
        while (sub_int_current_grid >= 2) {
            unsigned int n = sub_int_current_grid + 1;
            double h_x = (dom.x_max - dom.x_min) / sub_int_current_grid;
            double h_y = (dom.y_max - dom.y_min) / sub_int_current_grid;
            std::vector<std::vector<double>> v(n, std::vector<double>(n, 0.0));
            std::vector<std::vector<double>> f(n, std::vector<double>(n, 0.0));

            if (is_finest) {
                for (unsigned int i = 0; i < n; ++i) {
                    double x = dom.x_min + i * h_x;
                    for (unsigned int j = 0; j < n; ++j) {
                        double y = dom.y_min + j * h_y;
                        v[i][j] = u_guess(x, y);
                        f[i][j] = rhs_func(x, y);
                    }
                }

                // set up boundary conditions
                for (unsigned int i = 0; i < n; ++i) {
                    double x = dom.x_min + i * h_x;
                    double y = dom.y_min + i * h_y;
                    v[i][0]   = bc.bottom(x, dom.y_min);
                    v[i][n-1] = bc.top(x, dom.y_max);
                    v[0][i]   = bc.left(dom.x_min, y);
                    v[n-1][i] = bc.right(dom.x_max, y);
                }

                // take average at corners
                v[0][0]     = 0.5 * (bc.left(dom.x_min, dom.y_min)   + bc.bottom(dom.x_min, dom.y_min));
                v[n-1][0]   = 0.5 * (bc.right(dom.x_max, dom.y_min)  + bc.bottom(dom.x_max, dom.y_min));
                v[0][n-1]   = 0.5 * (bc.left(dom.x_min, dom.y_max)   + bc.top(dom.x_min, dom.y_max));
                v[n-1][n-1] = 0.5 * (bc.right(dom.x_max, dom.y_max)  + bc.top(dom.x_max, dom.y_max));

                is_finest = false;
            }

            grids.emplace_back(Grid2D{v, f});

            logger::debug(
                "Created grid (level {}): v.size() = {}, f.size() = {}",
                grids.size() - 1, v.size(), f.size()
            );

            if (n == 3) break;
            sub_int_current_grid /= 2;
        }

        logger::info("Created {} level multigrid", grids.size());
        return grids;
    }
}