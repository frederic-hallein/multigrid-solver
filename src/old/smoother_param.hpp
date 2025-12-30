#pragma once

struct SmootherParam {
    unsigned int nu_1 = 1;
    unsigned int nu_2 = 1;
    SmootherParam() = default;
    SmootherParam(unsigned int nu_1_, unsigned int nu_2_) : nu_1(nu_1_), nu_2(nu_2_) {}
};