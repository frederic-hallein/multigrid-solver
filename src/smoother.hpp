#include <vector>
#include <functional>

#include "common.hpp"
#include "stencils.hpp"

namespace smoother {
    enum class SmootherType { J, WJ, GS, RBGS };

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

                // TODO : ue stencil
            }
        }
        v = v_new;
    }

}
