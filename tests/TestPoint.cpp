#include <gtest/gtest.h>

#include "Point.h"

TEST(Point, test_constructor)
{
  std::vector<cv::Point2f> src;
  src.emplace_back(1, 2);
  src.emplace_back(2, 6);
  src.emplace_back(-3, 0.3);

  const auto actual = wip::convertToPoint2D(src);

  EXPECT_FLOAT_EQ(actual[0].x(), 1);
  EXPECT_FLOAT_EQ(actual[0].y(), 2);
  EXPECT_FLOAT_EQ(actual[1].x(), 2);
  EXPECT_FLOAT_EQ(actual[1].y(), 6);
  EXPECT_FLOAT_EQ(actual[2].x(), -3);
  EXPECT_FLOAT_EQ(actual[2].y(), 0.3);
}

TEST(Point, test_mult)
{
  std::vector<cv::Point2f> src;
  src.emplace_back(1, 2);
  src.emplace_back(2, 6);
  src.emplace_back(-3, 0.3);
  src.emplace_back(9, -4);
  std::vector<cv::Point2f> dst;
  dst.emplace_back(1.22135867, 0.93899514);
  dst.emplace_back(1.64745532, 1.07120274);
  dst.emplace_back(-189.32242839, -54.92238531);
  dst.emplace_back(1.89840739, 1.11539421);

  cv::Mat H = (cv::Mat_<float>(3, 3) << 0.89125166, 0.62396362, 0.24830436,
               0.46690387, 0.36307604, 0.64246972, 0.3591727, 0.29780192, 1);

  const auto src_ = wip::convertToPoint2D(src);
  const auto dst_ = H * src_;

  for (size_t i = 0; i < dst_.size(); i++)
  {
    EXPECT_NEAR(dst_[i].x(), dst[i].x, 1e-3);
    EXPECT_NEAR(dst_[i].y(), dst[i].y, 1e-3);
  }
}
