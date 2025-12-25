#include <vector>

namespace stencils {
    inline double helmholtz_1d(
        double v_x_min, double v_x_max,
        double f, double h, double sigma)
    {
        return (v_x_min + v_x_max - h*h * f) / (2.0 + sigma * h*h);
    }

    inline double helmholtz_2d(
        double v_x_min, double v_x_max,
        double v_y_min, double v_y_max,
        double f, double h, double sigma
    )
    {
        return (v_x_min + v_x_max + v_y_min + v_y_max - h*h * f) / (4.0 + sigma * h*h);
    }

    inline double helmholtz_3d(
        double v_x_min, double v_x_max,
        double v_y_min, double v_y_max,
        double v_z_min, double v_z_max,
        double f, double h, double sigma
    )
    {
        return (v_x_min + v_x_max + v_y_min + v_y_max + v_z_min + v_z_max - h*h * f) / (6.0 + sigma * h*h);
    }
}