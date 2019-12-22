#include <gtest/gtest.h>

#include <ImageCorrdinate.h>

TEST(ImageCoordinate, test_operators)
{
  wip::Point<float, 2> ic{1.2, 3.4};
  wip::Point<float, 2> ic2{-1.1, 0.4};

  EXPECT_FLOAT_EQ(ic[0], 1.2);
  EXPECT_FLOAT_EQ(ic[1], 3.4);
  EXPECT_FLOAT_EQ(ic[0], 1.2);
  EXPECT_FLOAT_EQ(ic[1], 3.4);
  EXPECT_FLOAT_EQ(ic2[0], -1.1);
  EXPECT_FLOAT_EQ(ic2[1], 0.4);
  // EXPECT_FLOAT_EQ((ic+ic2)[0], 0.1);
  // EXPECT_FLOAT_EQ((ic+ic2)[1], 3.8);
}
