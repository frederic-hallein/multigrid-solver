#include "cycle.hpp"

namespace cycle {
    std::vector<double> v_cycle(
        std::vector<double>& v,
        const std::vector<double>& f,
        double h,
        const SmootherParam& smoother_param
    )
    {
        // pre-smoothing
        for (unsigned int iter = 1; iter <= smoother_param.nu_1; ++iter) {
            // TODO
        }


        // post-smoothing
        for (unsigned int iter = 1; iter <= smoother_param.nu_2; ++iter) {
            // TODO
        }

        return {};
    }

    std::vector<double> w_cycle(
        std::vector<double>& v,
        const std::vector<double>& f,
        double h,
        const SmootherParam& smoother_param
    )
    {
        // pre-smoothing
        for (unsigned int iter = 1; iter <= smoother_param.nu_1; ++iter) {
            // TODO
        }


        // post-smoothing
        for (unsigned int iter = 1; iter <= smoother_param.nu_2; ++iter) {
            // TODO
        }

        return {};
    }
}