#include "multigrid.hpp"
#include "common.hpp"

MG::MG(
    Func1D rhs_func_1d,
    BoundaryCond1D boundary_1d,
    double x_min, double x_max,
    double alpha
)
    : rhs_func_1d(rhs_func_1d), boundary_1d_(boundary_1d),
      x_min_(x_min), x_max_(x_max),
      y_min_(0.0), y_max_(0.0),
      alpha_(alpha)
{
    // TODO : print out parameters used
}

MG::MG(
    Func2D rhs_func_2d,
    BoundaryCond2D boundary_2d,
    double x_min, double x_max,
    double y_min, double y_max,
    double alpha
)
    : rhs_func_2d(rhs_func_2d), boundary_2d_(boundary_2d),
      x_min_(x_min), x_max_(x_max),
      y_min_(y_min), y_max_(y_max),
      alpha_(alpha)
{
    // TODO : print out parameters used
}

void MG::run(
    unsigned int sub_int,
    smoother::SmootherType smoother_type,
    CycleType cycle_type,
    unsigned int nu_1,
    unsigned int nu_2,
    Func1D u_guess
)
{
    if (sub_int % 2 != 0) {
        // TODO : print error
        return;
    }

    // TODO : do other checks before doing anything

    initialize_grids_1d(sub_int, u_guess);

    set_smoother(smoother_type);

    // TODO: select correct cycle using switch
}

void MG::run(
    unsigned int sub_int,
    smoother::SmootherType smoother_type,
    CycleType cycle_type,
    unsigned int nu_1,
    unsigned int nu_2,
    Func2D u_guess
)
{
    if (sub_int % 2 != 0) {
        // TODO : print error
        return;
    }

    // TODO : do other checks before doing anything

    initialize_grids_2d(sub_int, u_guess);

    set_smoother(smoother_type);

    // TODO: select correct cycle using switch
    std::vector<double> v = v_cycle(nu_1, nu_2);
}

void MG::initialize_grids_1d(unsigned int sub_int, Func1D u_guess) {
    logger::info("Initializing grids for 1D problem.");
    grids_.clear();
    bool is_finest = true;
    unsigned int sub_int_current_grid = sub_int;
    while (sub_int_current_grid >= 2) {
        unsigned int n = sub_int_current_grid + 1;
        double h_level = (x_max_ - x_min_) / sub_int_current_grid;
        std::vector<double> v(n, 0.0);
        std::vector<double> f(n, 0.0);

        if (is_finest) {
            for (unsigned int i = 0; i < n; ++i) {
                double x = x_min_ + i * h_level;
                v[i] = u_guess(x);
                f[i] = rhs_func_1d(x);
            }
            is_finest = false;
        }

        grids_.emplace_back(Grid{v, f});

        logger::info(
            "Created grid (level {}): v.size() = {}, f.size() = {}",
            grids_.size() - 1, v.size(), f.size()
        );

        if (n == 3) break;
        sub_int_current_grid /= 2;
    }
}

void MG::initialize_grids_2d(unsigned int sub_int, Func2D u_guess) {
    logger::info("Initializing grids for 2D problem.");
    grids_.clear();
    bool is_finest = true;
    unsigned int sub_int_current_grid = sub_int;
    while (sub_int_current_grid >= 2) {
        unsigned int n = sub_int_current_grid + 1;
        double h_level = (x_max_ - x_min_) / sub_int_current_grid;
        std::vector<double> v(n * n, 0.0);
        std::vector<double> f(n * n, 0.0);

        if (is_finest) {
            for (unsigned int i = 0; i < n; ++i) {
                double x = x_min_ + i * h_level;
                for (unsigned int j = 0; j < n; ++j) {
                    double y = y_min_ + j * h_level;
                    int idx = flatten_2d_index(i, j, n);
                    v[idx] = u_guess(x, y);
                    f[idx] = rhs_func_2d(x, y);
                }
            }
            is_finest = false;
        }

        grids_.emplace_back(Grid{v, f});

        logger::info(
            "Created grid (level {}): v.size() = {}, f.size() = {}",
            grids_.size() - 1, v.size(), f.size()
        );

        if (n == 3) break;
        sub_int_current_grid /= 2;
    }
}

void MG::set_smoother(smoother::SmootherType smoother_type) {
    switch (smoother_type) {
        case smoother::SmootherType::J:
            // smooth_ = smoother::jacobi;
            break;
        case smoother::SmootherType::WJ:
            // smooth_ = smoother::weighted_jacobi;
            break;
        case smoother::SmootherType::GS:
            // smooth_ = smoother::gauss_seidel;
            break;
        case smoother::SmootherType::RBGS:
            // smooth_ = smoother::red_black_gauss_seidel;
            break;
    }
}

std::vector<double> MG::v_cycle(unsigned int nu_1, unsigned int nu_2) {

    // pre-smoothing
    for (unsigned int iter = 0; iter < nu_1; ++iter) {

    }

    // residual computation

    // restriction

    // recursion condition

    // prolongation

    // correction

    // post-smoothing
    for (unsigned int iter = 0; iter < nu_2; ++iter) {

    }

    return {};
}



