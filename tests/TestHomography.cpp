#include "gtest/gtest.h"

#include "Homography.h"

#include <iostream>
#include <string>

namespace wip
{
TEST(Homography, test_mat)
{
  std::vector<cv::Point2f> vecs{{0, 1}, {2, 3}};
  cv::Mat mat = cv::Mat(vecs, CV_32F);
  EXPECT_FLOAT_EQ(mat.at<float>(cv::Point(0, 0)), 0);
  EXPECT_FLOAT_EQ(mat.at<float>(cv::Point(1, 0)), 1);
  EXPECT_FLOAT_EQ(mat.at<float>(cv::Point(0, 1)), 2);
  EXPECT_FLOAT_EQ(mat.at<float>(cv::Point(1, 1)), 3);
}
} // namespace wip
