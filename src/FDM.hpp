#pragma once

namespace FDM {
    namespace cart {
        inline double helmholtz_1d(
            double v_x_neg, double v_x_pos,
            double f, double h, double sigma
        )
        {
            return (v_x_neg + v_x_pos + h*h * f) / (2.0 + sigma * h*h);
        }

        inline double helmholtz_2d(
            double v_x_neg, double v_x_pos,
            double v_y_neg, double v_y_pos,
            double f, double h, double sigma
        )
        {
            return (v_x_neg + v_x_pos + v_y_neg + v_y_pos + h*h * f) / (4.0 + sigma * h*h);
        }

        inline double helmholtz_3d(
            double v_x_neg, double v_x_pos,
            double v_y_neg, double v_y_pos,
            double v_z_neg, double v_z_pos,
            double f, double h, double sigma
        )
        {
            return (v_x_neg + v_x_pos + v_y_neg + v_y_pos + v_z_neg + v_z_pos + h*h * f) / (6.0 + sigma * h*h);
        }
    }

    // TODO : other coordinate namespaces
}