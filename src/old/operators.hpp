#pragma once

namespace operators {
    namespace cart {
        inline double helmholtz_1d(
            double v_x_neg, double v_x_cent, double v_x_pos,
            double h, double sigma
        )
        {
            return (-v_x_neg + 2 * v_x_cent - v_x_pos) / (h*h) + sigma * v_x_cent;
        }

    }
}