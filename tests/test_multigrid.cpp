#include <gtest/gtest.h>
#include "multigrid.hpp"

TEST(multigrid, initialize_grids_1d) {
    unsigned int n = 16;
    auto rhs = [](double) { return 1.0; };
    auto boundary = [](double) { return 0.0; };
    MG mg(rhs, boundary, 0.0, 1.0, 0.0);
    auto u_guess = [](double x) { return 0.0; };

    mg.initialize_grids_1d(n, u_guess);

    ASSERT_EQ(mg.grids_.size(), 4);

    EXPECT_EQ(mg.grids_[0].v.size(), 17);
    EXPECT_EQ(mg.grids_[0].f.size(), 17);

    EXPECT_EQ(mg.grids_[1].v.size(), 9);
    EXPECT_EQ(mg.grids_[1].f.size(), 9);

    EXPECT_EQ(mg.grids_[2].v.size(), 5);
    EXPECT_EQ(mg.grids_[2].f.size(), 5);

    EXPECT_EQ(mg.grids_[3].v.size(), 3);
    EXPECT_EQ(mg.grids_[3].f.size(), 3);
}

TEST(multigrid, initialize_grids_2d) {
    unsigned int n = 16;
    auto rhs = [](double, double) { return 1.0; };
    auto boundary = [](double, double) { return 0.0; };
    MG mg(rhs, boundary, 0.0, 1.0, 0.0, 1.0, 0.0);
    auto u_guess = [](double x, double y) { return 0.0; };

    mg.initialize_grids_2d(n, u_guess);

    ASSERT_EQ(mg.grids_.size(), 4);

    EXPECT_EQ(mg.grids_[0].v.size(), 289);
    EXPECT_EQ(mg.grids_[0].f.size(), 289);

    EXPECT_EQ(mg.grids_[1].v.size(), 81);
    EXPECT_EQ(mg.grids_[1].f.size(), 81);

    EXPECT_EQ(mg.grids_[2].v.size(), 25);
    EXPECT_EQ(mg.grids_[2].f.size(), 25);

    EXPECT_EQ(mg.grids_[3].v.size(), 9);
    EXPECT_EQ(mg.grids_[3].f.size(), 9);
}