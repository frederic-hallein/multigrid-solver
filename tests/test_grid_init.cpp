// #include <gtest/gtest.h>
// #include "grid_init.hpp"

// TEST(multigrid, initialize_grids_1d) {
//     unsigned int n = 16;
//     auto rhs = [](double) { return 1.0; };
//     auto u_guess = [](double) { return 0.0; };
//     auto boundary = [](double) { return 0.0; };
//     Domain1D dom{0.0, 1.0};
//     BoundaryCond1D bc{boundary, boundary};

//     auto grids = initialize_grids(rhs, u_guess, dom, bc, n);

//     ASSERT_EQ(grids.size(), 4);

//     EXPECT_EQ(grids[0].v.size(), 17);
//     EXPECT_EQ(grids[0].f.size(), 17);

//     EXPECT_EQ(grids[1].v.size(), 9);
//     EXPECT_EQ(grids[1].f.size(), 9);

//     EXPECT_EQ(grids[2].v.size(), 5);
//     EXPECT_EQ(grids[2].f.size(), 5);

//     EXPECT_EQ(grids[3].v.size(), 3);
//     EXPECT_EQ(grids[3].f.size(), 3);
// }

// TEST(multigrid, initialize_grids_2d) {
//     unsigned int n = 16;
//     auto rhs = [](double, double) { return 1.0; };
//     auto u_guess = [](double, double) { return 0.0; };
//     auto boundary = [](double, double) { return 0.0; };
//     Domain2D dom{0.0, 1.0, 0.0, 1.0};
//     BoundaryCond2D bc{boundary, boundary, boundary, boundary};

//     auto grids = initialize_grids(rhs, u_guess, dom, bc, n);

//     ASSERT_EQ(grids.size(), 4);

//     EXPECT_EQ(grids[0].v.size(), 289);
//     EXPECT_EQ(grids[0].f.size(), 289);

//     EXPECT_EQ(grids[1].v.size(), 81);
//     EXPECT_EQ(grids[1].f.size(), 81);

//     EXPECT_EQ(grids[2].v.size(), 25);
//     EXPECT_EQ(grids[2].f.size(), 25);

//     EXPECT_EQ(grids[3].v.size(), 9);
//     EXPECT_EQ(grids[3].f.size(), 9);
// }