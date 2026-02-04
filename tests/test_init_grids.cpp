#include <gtest/gtest.h>

#include "../src/multigrid/init_grids.hpp"

TEST(multigrid, init_grids_1d) {
    unsigned int n = 16;
    auto rhs = [](double) { return 1.0; };
    auto u_guess = [](double) { return 0.0; };
    auto boundary = [](double) { return 0.0; };
    Domain1D dom{0.0, 1.0};
    BoundaryCond1D bc{boundary, boundary};

    auto grids = multigrid::init_grids(rhs, u_guess, dom, bc, n);

    ASSERT_EQ(grids.size(), 4);

    EXPECT_EQ(grids[0].v.size(), 17);
    EXPECT_EQ(grids[0].f.size(), 17);

    EXPECT_EQ(grids[1].v.size(), 9);
    EXPECT_EQ(grids[1].f.size(), 9);

    EXPECT_EQ(grids[2].v.size(), 5);
    EXPECT_EQ(grids[2].f.size(), 5);

    EXPECT_EQ(grids[3].v.size(), 3);
    EXPECT_EQ(grids[3].f.size(), 3);
}

TEST(multigrid, init_grids_2d) {
    unsigned int n = 16;
    auto rhs       = [](double, double) { return 1.0; };
    auto u_guess   = [](double, double) { return 0.0; };
    auto bc_top    = [](double, double) { return 1.0; };
    auto bc_bottom = [](double, double) { return 2.0; };
    auto bc_left   = [](double, double) { return 3.0; };
    auto bc_right  = [](double, double) { return 4.0; };
    Domain2D dom{0.0, 1.0, 0.0, 1.0};
    BoundaryCond2D bc{bc_left, bc_right, bc_bottom, bc_top};

    auto grids = multigrid::init_grids(rhs, u_guess, dom, bc, n);

    ASSERT_EQ(grids.size(), 4);

    EXPECT_EQ(grids[0].v.size(),    17);
    EXPECT_EQ(grids[0].v[0].size(), 17);
    EXPECT_EQ(grids[0].f.size(),    17);
    EXPECT_EQ(grids[0].f[0].size(), 17);

    EXPECT_EQ(grids[1].v.size(),    9);
    EXPECT_EQ(grids[1].v[0].size(), 9);
    EXPECT_EQ(grids[1].f.size(),    9);
    EXPECT_EQ(grids[1].f[0].size(), 9);

    EXPECT_EQ(grids[2].v.size(),    5);
    EXPECT_EQ(grids[2].v[0].size(), 5);
    EXPECT_EQ(grids[2].f.size(),    5);
    EXPECT_EQ(grids[2].f[0].size(), 5);

    EXPECT_EQ(grids[3].v.size(),    3);
    EXPECT_EQ(grids[3].v[0].size(), 3);
    EXPECT_EQ(grids[3].f.size(),    3);
    EXPECT_EQ(grids[3].f[0].size(), 3);

    for (size_t level = 0; level < grids.size(); ++level) {
        EXPECT_EQ(grids[level].v.size(), grids[level].v[0].size());
        EXPECT_EQ(grids[level].f.size(), grids[level].f[0].size());
    }

    size_t n_level = grids[0].v.size();

    for (size_t i = 1; i < n_level - 1; ++i) {
        EXPECT_EQ(grids[0].v[i][0], 2.0);
        EXPECT_EQ(grids[0].v[i][n_level-1], 1.0);
    }

    for (size_t j = 1; j < n_level - 1; ++j) {
        EXPECT_EQ(grids[0].v[0][j], 3.0);
        EXPECT_EQ(grids[0].v[n_level-1][j], 4.0);
    }

    EXPECT_EQ(grids[0].v[0][0], 0.5 * (3.0 + 2.0)) ;
    EXPECT_EQ(grids[0].v[n_level - 1][0], 0.5 * (4.0 + 2.0));
    EXPECT_EQ(grids[0].v[0][n_level - 1], 0.5 * (3.0 + 1.0));
    EXPECT_EQ(grids[0].v[n_level - 1][n_level - 1], 0.5 * (4.0 + 1.0));
}
