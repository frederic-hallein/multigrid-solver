#include "multigrid.hpp"
#include "common.hpp"

MG::MG(
    Func1D rhs_func_1d,
    BoundaryCond boundary,
    double x_min, double x_max,
    double alpha
)
    : rhs_func_1d(rhs_func_1d), boundary_(boundary),
      x_min_(x_min), x_max_(x_max),
      y_min_(0.0), y_max_(0.0),
      alpha_(alpha)
{
    // TODO : print out parameters used
}

MG::MG(
    Func2D rhs_func_2d,
    BoundaryCond boundary,
    double x_min, double x_max,
    double y_min, double y_max,
    double alpha
)
    : rhs_func_2d(rhs_func_2d), boundary_(boundary),
      x_min_(x_min), x_max_(x_max),
      y_min_(y_min), y_max_(y_max),
      alpha_(alpha)
{
    // TODO : print out parameters used
}

void MG::run(
    unsigned int n,
    smoother::SmootherType smoother_type,
    CycleType cycle_type,
    unsigned int nu_1,
    unsigned int nu_2,
    Func1D u_guess
)
{
    if (n % 2 != 0) {
        // TODO : print error
        return;
    }

    // TODO : do other checks before ding anything

    initialize_grids_1d(n, u_guess);

    set_smoother(smoother_type);

    // TODO: select correct cycle using switch
}

void MG::run(
    unsigned int n,
    smoother::SmootherType smoother_type,
    CycleType cycle_type,
    unsigned int nu_1,
    unsigned int nu_2,
    Func2D u_guess
)
{
    double h = (x_max_ - x_min_) / (n - 1); // grid spacing
    // TODO : print out parameters used


    std::vector<double> v((n+1)*(n+1), 0.0);
    std::vector<double> f((n+1)*(n+1), 0.0);

    for (unsigned int i = 0; i <= n; ++i) {
        double x = x_min_ + i * h;
        for (unsigned int j = 0; j <= n; ++j) {
            double y = y_min_ + j * h;
            int idx = flatten_2d_index(i, j, n+1);
            v[idx] = u_guess(x, y);
            f[idx] = rhs_func_2d(x, y);
        }
    }

    Grid grid{v, f};

    set_smoother(smoother_type);

    // TODO: select correct cycle using switch
}

void MG::initialize_grids_1d(unsigned int n, Func1D u_guess) {
    double h = (x_max_ - x_min_) / (n - 1);
    grids_.clear();
    unsigned int coarse_level = n;
    bool is_finest = true;

    while (coarse_level >= 2) {
        double h_level = (x_max_ - x_min_) / coarse_level;
        std::vector<double> v(coarse_level + 1, 0.0);
        std::vector<double> f(coarse_level + 1, 0.0);

        if (is_finest) {
            for (unsigned int i = 0; i <= coarse_level; ++i) {
                double x = x_min_ + i * h_level;
                v[i] = u_guess(x);
                f[i] = rhs_func_1d(x);
            }
            is_finest = false;
        }

        grids_.emplace_back(Grid{v, f});

        if (coarse_level == 2) break;
        coarse_level /= 2;
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
    for (unsigned int iter = 0; iter < nu_1; ++iter) {

    }

    return {};
}



