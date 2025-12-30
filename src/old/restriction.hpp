#pragma once

namespace restriction {
    namespace cart {
        inline double full_weighted_1d(
            double vh_x_neg,
            double vh_x_cent,
            double vh_x_pos
        )
        {
            return (vh_x_neg + 2 * vh_x_cent + vh_x_pos) / 4.0;
        }
    }
}