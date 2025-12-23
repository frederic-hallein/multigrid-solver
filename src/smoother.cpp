#include "smoother.hpp"

namespace smoother {
    void jacobi(
        std::vector<double>& v,
        const std::vector<double>& f,
        unsigned int n,
        double h
    )
    {
        std::vector<double> v_new(v.size());
        for (unsigned int i = 0; i < n; ++i) {
            for (unsigned int j = 0; j < n; ++j) {
                // TODO : handle BC

                // TODO : use stencil
            }
        }
        v = v_new;
    }
}