#include <vector>

namespace stencils {
    inline double helmholtz_1d(
        double v_x_minus, double v_x_plus,
        double f, double h, double alpha)
    {
        return (v_x_minus + v_x_plus - h*h * f) / (2.0 + alpha * h*h);
    }

    inline double helmholtz_2d(
        double v_x_minus, double v_x_plus,
        double v_y_minus, double v_y_plus,
        double f, double h, double alpha
    )
    {
        return (v_x_minus + v_x_plus + v_y_minus + v_y_plus - h*h * f) / (4.0 + alpha * h*h);
    }

    inline double helmholtz_3d(
        double v_x_minus, double v_x_plus,
        double v_y_minus, double v_y_plus,
        double v_z_minus, double v_z_plus,
        double f, double h, double alpha
    )
    {
        return (v_x_minus + v_x_plus + v_y_minus + v_y_plus + v_z_minus + v_z_plus - h*h * f) / (6.0 + alpha * h*h);
    }
}