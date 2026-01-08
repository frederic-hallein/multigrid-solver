#include "multigrid/pde.hpp"
#include "multigrid/run.hpp"

double u_exact(double x) {
    return x * (1.0 - x);
}

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

    return 0;
}