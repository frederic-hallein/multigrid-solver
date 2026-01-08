#include "multigrid/pde.hpp"
#include "multigrid/run.hpp"

// #include "multigrid/cartesian_2d/pde.hpp"
// #include "multigrid/cartesian_2d/run.hpp"


double u_exact(double x) {
    return x * (1.0 - x);
}


// double u_exact(double x, double y) {
//     return x * x * y * y * (1.0 - x * x) * (y * y - 1.0);
// }

int main() {

    Config config;
    multigrid::ModHelmholtz pde {
        0.0,
        Domain1D { 0.0, 1.0 },
        BoundaryCond1D {
            [](double) { return 0.0; },
            [](double) { return 0.0; }
        },
        [](double) { return 2.0; }
    };

    auto results = multigrid::run(
        pde, config, u_exact
    );

    // multigrid::cartesian_2d::ModHelmholtz pde {
    //     0.0,
    //     Domain2D {
    //         0.0, 1.0,
    //         0.0, 1.0
    //     },
    //     BoundaryCond2D {
    //         [](double, double) { return 0.0; },
    //         [](double, double) { return 0.0; }
    //     },
    //     [](double x, double y) { return 2.0 * ((1.0 - 6.0 * x * x) * y * y * (1.0 - y * y) + (1.0 - 6.0 * y * y) * x * x * (1.0 - x * x)); }
    // };

    // auto results = multigrid::cartesian_2d::run(
    //     pde, config, u_exact
    // );

    return 0;
}
